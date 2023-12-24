#include "myglwidget.h"
#include <GL/glew.h>
#include <algorithm>

MyGLWidget::MyGLWidget(QWidget *parent)
	:QOpenGLWidget(parent) {}

MyGLWidget::~MyGLWidget() {
	delete[] render_buffer;
	delete[] temp_render_buffer;
	delete[] temp_z_buffer;
	delete[] z_buffer;
}

void MyGLWidget::resizeBuffer(int newW, int newH) {
	delete[] render_buffer;
	delete[] temp_render_buffer;
	delete[] temp_z_buffer;
	delete[] z_buffer;
	WindowSizeW = newW;
	WindowSizeH = newH;
	render_buffer = new vec3[WindowSizeH * WindowSizeW];
	temp_render_buffer = new vec3[WindowSizeH * WindowSizeW];
	temp_z_buffer = new float[WindowSizeH * WindowSizeW];
	z_buffer = new float[WindowSizeH * WindowSizeW];
}

void MyGLWidget::initializeGL() {
	WindowSizeW = width();
	WindowSizeH = height();
	glViewport(0, 0, WindowSizeW, WindowSizeH);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_DEPTH_TEST);
	offset = vec2(WindowSizeH / 2, WindowSizeW / 2);
	// 对定义的数组初始化
	render_buffer = new vec3[WindowSizeH * WindowSizeW];
	temp_render_buffer = new vec3[WindowSizeH * WindowSizeW];
	temp_z_buffer = new float[WindowSizeH * WindowSizeW];
	z_buffer = new float[WindowSizeH * WindowSizeW];
	for (int i = 0; i < WindowSizeH * WindowSizeW; i++) {
		render_buffer[i] = vec3(0, 0, 0);
		temp_render_buffer[i] = vec3(0, 0, 0);
		temp_z_buffer[i] = MAX_Z_BUFFER;
		z_buffer[i] = MAX_Z_BUFFER;
	}
}

void MyGLWidget::keyPressEvent(QKeyEvent *e) {

	switch (e->key()) {
	case Qt::Key_1: objModel.loadModel("./objs/singleTriangle.obj"); update(); break;
	case Qt::Key_2: objModel.loadModel("./objs/teapot_600.obj"); update(); break;
	case Qt::Key_3: objModel.loadModel("./objs/teapot_8000.obj"); update(); break;
	case Qt::Key_4: objModel.loadModel("./objs/rock.obj"); update(); break;
	case Qt::Key_5: objModel.loadModel("./objs/cube.obj"); update(); break;
	case Qt::Key_0: degree += 35; update(); break;
	}
}

void MyGLWidget::paintGL() {
	scene();
}
void MyGLWidget::clearBuffer(vec3 *now_buffer) {
	for (int i = 0; i < WindowSizeH * WindowSizeW; i++) {
		now_buffer[i] = vec3(0, 0, 0);
	}
}

void MyGLWidget::clearBuffer(int *now_buffer) {
	memset(now_buffer, 0, WindowSizeW * WindowSizeH * sizeof(int));
}


void MyGLWidget::clearZBuffer(float *now_buffer) {
	std::fill(now_buffer, now_buffer + WindowSizeW * WindowSizeH, MAX_Z_BUFFER);
}


// 窗口大小变动后，需要重新生成render_buffer等数组
void MyGLWidget::resizeGL(int w, int h) {
	resizeBuffer(w, h);
	offset = vec2(WindowSizeH / 2, WindowSizeW / 2);
	clearBuffer(render_buffer);
}

void MyGLWidget::scene() {
	// 自主设置变换矩阵
	camPosition = vec3(100 * sin(degree * 3.14 / 180.0) + objModel.centralPoint.y, 100 * cos(degree * 3.14 / 180.0) + objModel.centralPoint.x, 10 + objModel.centralPoint.z);
	camLookAt = objModel.centralPoint;     // 例如，看向物体中心
	camUp = vec3(0, 1, 0);         // 上方向向量
	projMatrix = glm::perspective(radians(20.0f), 1.0f, 0.1f, 2000.0f);

	// 单一点光源，可以改为数组实现多光源
	lightPosition = objModel.centralPoint + vec3(0, 100, 100);
	clearBuffer(render_buffer);
	clearZBuffer(z_buffer);
	for (int i = 0; i < objModel.triangleCount; i++) {
		Triangle nowTriangle = objModel.getTriangleByID(i);
		drawTriangle(nowTriangle);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	renderWithTexture(render_buffer, WindowSizeH, WindowSizeW);
}

void MyGLWidget::drawTriangle(Triangle triangle) {
	// 三维顶点映射到二维平面
	vec3 *vertices = triangle.triangleVertices;
	vec3 *normals = triangle.triangleNormals;
	FragmentAttr transformedVertices[3];
	clearBuffer(this->temp_render_buffer);
	clearZBuffer(this->temp_z_buffer);
	mat4 viewMatrix = glm::lookAt(camPosition, camLookAt, camUp);

	for (int i = 0; i < 3; ++i) {
		vec4 ver_mv = viewMatrix * vec4(vertices[i], 1.0f);
		float nowz = glm::length(camPosition - vec3(ver_mv));
		vec4 ver_proj = projMatrix * ver_mv;
		transformedVertices[i].x = ver_proj.x + offset.x;
		transformedVertices[i].y = ver_proj.y + offset.y;
		transformedVertices[i].z = nowz;
		transformedVertices[i].pos_mv = ver_mv;
		mat3 normalMatrix = mat3(viewMatrix);
		vec3 normal_mv = normalMatrix * normals[i];
		transformedVertices[i].normal = normal_mv;
	}

	// 将当前三角形渲染在temp_buffer中

	// HomeWork: 2: 用edge-walking填充三角形内部到temp_buffer中
	vec2 changeLine = edge_walking(transformedVertices);

	// HomeWork: 1、绘制三角形三边
	bresenham(transformedVertices[0], transformedVertices[1], 1);
	bresenham(transformedVertices[1], transformedVertices[2], 2);
	bresenham(transformedVertices[2], transformedVertices[0], 3);

	// 合并temp_buffer 到 render_buffer, 深度测试
	// 从firstChangeLine开始遍历，可以稍快
	for (int h = changeLine.x; h <= changeLine.y; h++) {
		auto render_row = &render_buffer[h * WindowSizeW];
		auto temp_render_row = &temp_render_buffer[h * WindowSizeW];
		auto z_buffer_row = &z_buffer[h * WindowSizeW];
		auto temp_z_buffer_row = &temp_z_buffer[h * WindowSizeW];
		for (int i = 0; i < WindowSizeW; i++) {
			if (z_buffer_row[i] < temp_z_buffer_row[i])
				continue;
			else {
				z_buffer_row[i] = temp_z_buffer_row[i];
				render_row[i] = temp_render_row[i];
			}
		}

	}
}

inline int MyGLWidget::posConvert(const int &x, const int &y) { return (0 <= x && x < WindowSizeW && 0 <= y && y < WindowSizeH) ? y * WindowSizeW + x : 0; }

vec2 MyGLWidget::edge_walking(FragmentAttr *p) {
	for (int i = 0; i < 3; ++i)
		for (int j = i + 1; j < 3; ++j)
			if (p[i].x > p[j].x)
				std::swap(p[i], p[j]);

	float d1 = (float)(p[1].y - p[0].y) / (float)(p[1].x - p[0].x);
	float d2 = (float)(p[2].y - p[0].y) / (float)(p[2].x - p[0].x);

	for (int x = p[0].x; x < p[1].x; ++x) {
		int y1 = d1 * (float)(x - p[0].x) + (float)(p[0].y);
		int y2 = d2 * (float)(x - p[0].x) + (float)(p[0].y);
		if (y1 > y2) std::swap(y1, y2);
		for (int y = y1; y <= y2; ++y) {
			int pos = posConvert(y, x);
			FragmentAttr loc;
			loc.pos_mv = p[0].pos_mv + ((p[1].pos_mv - p[0].pos_mv) * (float)(x - p[0].x) + (p[2].pos_mv - p[0].pos_mv) * (float)(y - p[0].y)) / (float)((p[1].x - p[0].x) * (p[2].y - p[0].y) - (p[2].x - p[0].x) * (p[1].y - p[0].y));
			loc.normal = p[0].normal + ((p[1].normal - p[0].normal) * (float)(x - p[0].x) + (p[2].normal - p[0].normal) * (float)(y - p[0].y)) / (float)((p[1].x - p[0].x) * (p[2].y - p[0].y) - (p[2].x - p[0].x) * (p[1].y - p[0].y));
			temp_render_buffer[pos] = PhoneShading(loc);
			temp_z_buffer[pos] = p[0].z + ((float)(x - p[0].x) * (p[1].z - p[0].z) + (float)(y - p[0].y) * (p[2].z - p[0].z)) / (float)((p[1].x - p[0].x) * (p[2].y - p[0].y) - (p[2].x - p[0].x) * (p[1].y - p[0].y));
		}
	}

	d1 = (float)(p[2].y - p[1].y) / (float)(p[2].x - p[1].x);

	for (int x = p[1].x; x < p[2].x; ++x) {
		int y1 = d1 * (float)(x - p[1].x) + (float)(p[1].y);
		int y2 = d2 * (float)(x - p[0].x) + (float)(p[0].y);
		if (y1 > y2) std::swap(y1, y2);
		for (int y = y1; y <= y2; ++y) {
			int pos = posConvert(y, x);
			FragmentAttr loc;
			loc.pos_mv = p[0].pos_mv + ((p[1].pos_mv - p[0].pos_mv) * (float)(x - p[0].x) + (p[2].pos_mv - p[0].pos_mv) * (float)(y - p[0].y)) / (float)((p[1].x - p[0].x) * (p[2].y - p[0].y) - (p[2].x - p[0].x) * (p[1].y - p[0].y));
			loc.normal = p[0].normal + ((p[1].normal - p[0].normal) * (float)(x - p[0].x) + (p[2].normal - p[0].normal) * (float)(y - p[0].y)) / (float)((p[1].x - p[0].x) * (p[2].y - p[0].y) - (p[2].x - p[0].x) * (p[1].y - p[0].y));
			temp_render_buffer[pos] = PhoneShading(loc);
			temp_z_buffer[pos] = p[0].z + ((float)(x - p[0].x) * (p[1].z - p[0].z) + (float)(y - p[0].y) * (p[2].z - p[0].z)) / (float)((p[1].x - p[0].x) * (p[2].y - p[0].y) - (p[2].x - p[0].x) * (p[1].y - p[0].y));
		}
	}

	return vec2(p[0].x, p[2].x);
}

vec3 MyGLWidget::PhoneShading(FragmentAttr &nowPixelResult) {
	vec3 ambientColor = vec3(0.2f, 0.2f, 0.2f); // 环境光颜色
	vec3 diffuseColor = vec3(0.8f, 0.8f, 0.8f); // 漫反射颜色
	vec3 specularColor = vec3(1.0f, 1.0f, 1.0f); // 镜面反射颜色
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f); // 光源颜色

	vec3 lightDirection = glm::normalize(lightPosition - nowPixelResult.pos_mv); // 光源方向
	vec3 normal = glm::normalize(nowPixelResult.normal); // 法线向量

	// 计算环境光照
	vec3 ambient = ambientColor * lightColor;

	// 计算漫反射光照
	float diffuseFactor = glm::max(glm::dot(normal, lightDirection), 0.0f);
	vec3 diffuse = diffuseColor * lightColor * diffuseFactor;

	// 计算镜面反射光照
	vec3 viewDirection = glm::normalize(camPosition - nowPixelResult.pos_mv); // 视线方向
	vec3 reflectDirection = glm::reflect(-lightDirection, normal); // 反射光线方向
	float specularFactor = glm::pow(glm::max(glm::dot(viewDirection, reflectDirection), 0.0f), 32.0f);
	vec3 specular = specularColor * lightColor * specularFactor;

	// 综合所有光照分量
	vec3 finalColor = ambient + diffuse + specular;
	return finalColor;
}

void MyGLWidget::bresenham(FragmentAttr &start, FragmentAttr &end, int id) {
	int x0 = start.x, y0 = start.y;
	int x1 = end.x, y1 = end.y;
	float z0 = start.z, z1 = end.z;
	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		std::swap(x0, y0);
		std::swap(x1, y1);
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
		std::swap(z0, z1);
	}

	int dx = x1 - x0;
	int dy = abs(y1 - y0);
	int err = dx / 2;
	int ystep = (y0 < y1) ? 1 : -1;
	int y = y0;
	for (int x = x0; x <= x1; ++x) {
		int pos = !steep ? posConvert(y, x) : posConvert(x, y);
		float delta = (float)(x - x0) / (float)(dx);
		temp_render_buffer[pos] = vec3(0.6015625, 1, 0.6015625);
		temp_z_buffer[pos] = delta * z0 + (1.0f - delta) * z1;
		err -= dy;
		if (err < 0) {
			y += ystep;
			err += dx;
		}
	}
}

void MyGLWidget::DDA(FragmentAttr &start, FragmentAttr &end, int id) {
	float dx = end.x - start.x;
	float dy = end.y - start.y;
	float step = max(fabs(dx), fabs(dy));
	dx /= step, dy /= step;

	float x = start.x, y = start.y;
	for (int i = 0; i < step; ++i) {
		x += dx, y += dy;
		int pos = posConvert((int)(y + 0.5), (int)(x + 0.5));
		temp_render_buffer[pos] = vec3(0.6015625, 1, 0.6015625);
		temp_z_buffer[pos] = (float)(i) / step * (end.z - start.z) + start.z;
	}
}

