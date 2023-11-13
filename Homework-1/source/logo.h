#ifndef LOGO_H
#define LOGO_H

#include <qopengl.h>
#include <QList>
#include <QVector3D>

class Logo {
public:
    Logo(); // 构造函数
    const GLfloat *constData() const { return m_data.constData(); } // 返回数据指针
    int count() const { return m_count; } // 返回数据数量
    int vertexCount() const { return m_count / 6; } // 返回顶点数量

private:
    void quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4); // 绘制顶面和底面
    void extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2); // 绘制侧面
    void add(const QVector3D &v, const QVector3D &n);

    QList<GLfloat> m_data; // 存储顶点数据的列表
    int m_count = 0; // 当前顶点数量
};

#endif // LOGO_H