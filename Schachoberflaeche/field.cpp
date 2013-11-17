#include "field.h"
#include <QtGui>

Field::Field(Farbe backgroundColor, Position positionDesFeldes, Figuren firgur, QWidget *parent)
    : QFrame(parent)
{
    setMinimumSize(100,100);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    this->setGeometry(0,0,300,100);
    if (backgroundColor == WEISS) {
        this->setStyleSheet("background-color:grey;");
    } else if (backgroundColor == SCHWARZ) {
        this->setStyleSheet("background-color:white;");
    } else {
		this->setStyleSheet("background-color:blue;");
	}

    figure = new QLabel(this);
	f.open("debug.txt",ios::out);
}

void Field::changePicture(pair<Figuren, Farbe>* figur) {
	const QPixmap* bild = figureToPicture(figur);
	figure->setPixmap(*bild);
	figure->show();
	figure->setAttribute(Qt::WA_DeleteOnClose);
}

QPixmap* Field::figureToPicture(pair<Figuren, Farbe>* figur) {
	QString bild;
	switch (figur->first)
	{
	case KOENIG:
		bild = ":/images/Koenig-";
		break;
	case DAME:
		bild = ":/images/Dame-";
		break;
	case BAUER:
		bild = ":/images/Bauer-";
		break;
	case TURM:
		bild = ":/images/Turm-";
		break;
	case LAEUFER:
		bild = ":/images/Laeufer-";
		break;
	case SPRINGER:
		bild = ":/images/Springer-";
		break;
	default:
		return new QPixmap(":/images/empty.png");
	}
	if(figur->second==SCHWARZ) {
		bild += "schwarz.png";
	} else {
		bild += "weis.png";
	}
	return new QPixmap(bild);
}

void Field::dragEnterEvent(QDragEnterEvent *event)
 {
	 f << "dragEnterEvent" << std::endl;
	 if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         if (event->source() == this) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }
 }

 void Field::dragMoveEvent(QDragMoveEvent *event)
 {
	 f << "dragMoveEvent" << std::endl;
     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         if (event->source() == this) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }
 }

 void Field::dropEvent(QDropEvent *event)
 {
	 f << ("dropEvent") << std::endl;
     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
         QDataStream dataStream(&itemData, QIODevice::ReadOnly);

         QPixmap pixmap;
         QPoint offset;
         dataStream >> pixmap >> offset;

         QLabel *newIcon = new QLabel(this);
         newIcon->setPixmap(pixmap);
         newIcon->move(event->pos() - offset);
         newIcon->show();
         newIcon->setAttribute(Qt::WA_DeleteOnClose);

         if (event->source() == this) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }
 }

 void Field::mousePressEvent(QMouseEvent *event)
 {
	 f << ("mousePressEvent") << std::endl;
     QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
     if (!child)
         return;

     QPixmap pixmap = *child->pixmap();

     QByteArray itemData;
     QDataStream dataStream(&itemData, QIODevice::WriteOnly);
     dataStream << pixmap << QPoint(event->pos() - child->pos());

     QMimeData *mimeData = new QMimeData;
     mimeData->setData("application/x-dnditemdata", itemData);

     QDrag *drag = new QDrag(this);
     drag->setMimeData(mimeData);
     drag->setPixmap(pixmap);
     drag->setHotSpot(event->pos() - child->pos());

     QPixmap tempPixmap = pixmap;
     QPainter painter;
     painter.begin(&tempPixmap);
     painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
     painter.end();

     child->setPixmap(tempPixmap);

     if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
         child->close();
     else {
         child->show();
         child->setPixmap(pixmap);
     }
 }


Field::~Field()
{
	f.close();
}
