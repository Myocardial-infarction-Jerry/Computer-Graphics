#include "logo.h"
#include <qmath.h>

Logo::Logo() {
    m_data.resize(2500 * 6); // 设置顶点数据的大小

    const GLfloat unit = 0.60f / 14.0f;

    // // Letter L
    quad(-7.00f * unit, 2.50 * unit, -7.00f * unit, -2.50f * unit, -6.00f * unit, -2.50f * unit, -6.00f * unit, 2.50f * unit);
    quad(-6.00f * unit, -1.50 * unit, -6.00f * unit, -2.50f * unit, -3.00f * unit, -2.50f * unit, -3.00f * unit, -1.50f * unit);
    extrude(-6.00f * unit, 2.50f * unit, -7.00f * unit, 2.50f * unit);
    extrude(-7.00f * unit, 2.50f * unit, -7.00f * unit, -2.50f * unit);
    extrude(-7.00f * unit, -2.50f * unit, -3.00f * unit, -2.50f * unit);
    extrude(-3.00f * unit, -2.50f * unit, -3.00f * unit, -1.50f * unit);
    extrude(-3.00f * unit, -1.50f * unit, -6.00f * unit, -1.50f * unit);
    extrude(-6.00f * unit, -1.50f * unit, -6.00f * unit, 2.50f * unit);

    // Letter S
    const int NumSectors = 50;

    for (int i = 0; i < NumSectors; ++i) {
        GLfloat angle = i * 1.50f * M_PI / NumSectors;
        GLfloat angleCos = qCos(angle);
        GLfloat angleSin = qSin(angle);
        const GLfloat x1 = 1.00f * unit * angleCos;
        const GLfloat y1 = 0.50f * unit * angleSin + unit;
        const GLfloat x2 = 2.00f * unit * angleCos;
        const GLfloat y2 = 1.50f * unit * angleSin + unit;

        angle = (i + 1) * 1.50f * M_PI / NumSectors;
        angleCos = qCos(angle);
        angleSin = qSin(angle);
        const GLfloat x3 = 2.00f * unit * angleCos;
        const GLfloat y3 = 1.50f * unit * angleSin + unit;
        const GLfloat x4 = 1.00f * unit * angleCos;
        const GLfloat y4 = 0.50f * unit * angleSin + unit;

        quad(x1, y1, x2, y2, x3, y3, x4, y4);
        extrude(x4, y4, x1, y1);
        extrude(x2, y2, x3, y3);
        quad(-x1, -y1, -x2, -y2, -x3, -y3, -x4, -y4);
        extrude(-x4, -y4, -x1, -y1);
        extrude(-x2, -y2, -x3, -y3);
    }

    extrude(1.00f * unit, 1.00f * unit, 2.00f * unit, 1.00f * unit);
    extrude(-1.00f * unit, -1.00f * unit, -2.00f * unit, -1.00f * unit);

    // Letter Y
    quad(3.00f * unit, 2.50f * unit, 4.50f * unit, 0.00f * unit, 5.50f * unit, 0.00f * unit, 4.00f * unit, 2.50f * unit);
    quad(6.00f * unit, 2.50f * unit, 4.50f * unit, 0.00f * unit, 5.50f * unit, 0.00f * unit, 7.00f * unit, 2.50f * unit);
    quad(4.50f * unit, 0.00f * unit, 4.50f * unit, -2.50f * unit, 5.50f * unit, -2.50f * unit, 5.50f * unit, 0.00f * unit);
    extrude(4.00f * unit, 2.50f * unit, 3.00f * unit, 2.50f * unit);
    extrude(3.00f * unit, 2.50f * unit, 4.50f * unit, 0.00f * unit);
    extrude(4.50f * unit, 0.00f * unit, 4.50f * unit, -2.50f * unit);
    extrude(4.50f * unit, -2.50f * unit, 5.50f * unit, -2.50f * unit);
    extrude(5.50f * unit, -2.50f * unit, 5.50f * unit, 0.00f * unit);
    extrude(5.50f * unit, 0.00f * unit, 7.00f * unit, 2.50f * unit);
    extrude(7.00f * unit, 2.50f * unit, 6.00f * unit, 2.50f * unit);
    extrude(6.00f * unit, 2.50f * unit, 4.50f * unit, 0.00f * unit);
    extrude(5.00f * unit, 0.00f * unit, 4.00f * unit, 2.50f * unit);
}

void Logo::add(const QVector3D &v, const QVector3D &n) {
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    m_count += 6;
}

void Logo::quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4) {
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, -0.05f), n);
    add(QVector3D(x4, y4, -0.05f), n);
    add(QVector3D(x2, y2, -0.05f), n);

    add(QVector3D(x3, y3, -0.05f), n);
    add(QVector3D(x2, y2, -0.05f), n);
    add(QVector3D(x4, y4, -0.05f), n);

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));

    add(QVector3D(x4, y4, 0.05f), n);
    add(QVector3D(x1, y1, 0.05f), n);
    add(QVector3D(x2, y2, 0.05f), n);

    add(QVector3D(x2, y2, 0.05f), n);
    add(QVector3D(x3, y3, 0.05f), n);
    add(QVector3D(x4, y4, 0.05f), n);
}

void Logo::extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.1f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, +0.05f), n);
    add(QVector3D(x1, y1, -0.05f), n);
    add(QVector3D(x2, y2, +0.05f), n);

    add(QVector3D(x2, y2, -0.05f), n);
    add(QVector3D(x2, y2, +0.05f), n);
    add(QVector3D(x1, y1, -0.05f), n);
}