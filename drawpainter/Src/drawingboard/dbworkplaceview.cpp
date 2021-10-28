#include "dbworkplaceview.h"
#include <QCursor>
dbworkplaceview::dbworkplaceview(QWidget *parent = 0)
    :QGraphicsView(parent)
{
    viewport()->setCursor(QCursor(Qt::CrossCursor));
}
