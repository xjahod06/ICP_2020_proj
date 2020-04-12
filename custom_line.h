#ifndef CUSTOM_LINE_H
#define CUSTOM_LINE_H

#include <QGraphicsLineItem>
#include <QVariantAnimation>
#include <QTimer>

class custom_line :public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit custom_line(QGraphicsItem *parent = nullptr, QColor color = Qt::red);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    virtual QRectF boundingRect() const override;

private:
    QVariantAnimation *anim{nullptr};
    qreal station{0.0};
    qreal move{0.0};
    QTimer *timer;
    void time_line();

private slots:
    void on_animation(const QVariant &value);

};

#endif // CUSTOM_LINE_H
