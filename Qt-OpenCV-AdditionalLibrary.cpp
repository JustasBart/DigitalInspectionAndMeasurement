#include "Qt-OpenCV-AdditionalLibrary.h"

QPixmap MatToQPixmap(const Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS=1
    if(mat.type() == CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i = 0; i < 256; i++)
            colorTable.push_back(qRgb(i, i, i));
        // Copy input Mat
        const uchar *qImageBuffer = const_cast<const uchar*>(mat.data);
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return QPixmap::fromImage(img);
        //return img;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = const_cast<const uchar*>(mat.data);
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return QPixmap::fromImage(img.rgbSwapped());
    }
    else if(mat.type() == CV_8UC4)
    {
        // Copy input Mat
        const uchar *qImageBuffer = const_cast<const uchar*>(mat.data);
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return QPixmap::fromImage(img.rgbSwapped());
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QPixmap();
    }
}
