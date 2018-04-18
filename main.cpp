#include <QCoreApplication>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QDomElement>
#include <QDomDocument>
#include <QtMath>

QDomDocument doc("mydocument");
QFile file("/home/ryu/Software/dlib-19.10/examples/faces/training.xml");
double inputWidth,inputHeigh,inputTop, inputLeft,outputWidth,outputHeigh,outputTop,outputLeft;
double ratio=0.5;
double minW =1000, minH=1000;
double minRatio=1,maxRatio=0;
double minArea=100000;
void SaveXML()
{
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug("cant write able");
    }
    QTextStream stream;
    stream.setDevice(&file);
    doc.save(stream,1);
    file.close();
    qDebug("file closed");
}
void DisplayRatio()
{
//    double result = outputWidth/outputHeigh;
//    if(maxRatio<result) maxRatio=result;
//    if(minRatio>result) minRatio=result;
//    if(minW>outputWidth)
//        minW = outputWidth;
//    if(minH>outputHeigh)
//        minH = outputHeigh;
//    if((outputHeigh*outputWidth)<minArea)
//        minArea = outputHeigh*outputWidth;
    double result = inputWidth/inputHeigh;
    if(maxRatio<result) maxRatio=result;
    if(minRatio>result) minRatio=result;
    if(minW>inputWidth)
        minW = inputWidth;
    if(minH>inputHeigh)
        minH = inputHeigh;
    if((inputHeigh*inputWidth)<minArea)
        minArea = inputHeigh*inputWidth;
    qDebug()<<"ratio: "<<result<<"\n" ;
}
void setOutputValue(/*double inputWidth, double inputHeigh, double inputLeft, double inputTop*/)
{
    /* assume standar ratio is 1/2
     * if w/h>0.5 = >raise h
     * if w/h<0.5 => raise w
    */


    double result = inputWidth/inputHeigh;
    int raise=0;
    qDebug()<<"result "<<result;
    if(result>=1)
    {
     qDebug("input error");
    }
    else if(result>ratio)
    {
        //rasie h, change top
        //outH = inW*2 && (outH-inH)%2==0
        outputHeigh = qCeil(inputWidth*2);
        outputWidth = inputWidth;
//        outputWidth = inputWidth;
//        outputLeft = inputLeft ;
//         raise = (inputWidth*2)-inputHeigh;
//        if(raise%2!=0)
//        {
//            outputHeigh = inputHeigh+(raise/2);
//            outputTop = inputTop-((raise/2)+1);
//        }
//        else{
//            outputHeigh = inputHeigh+(raise/2);
//            outputTop = inputTop-(raise/2);
//        }
    }
    else if(result<ratio){
        //raise w, change left
        outputWidth = qCeil(inputHeigh/2);
        outputHeigh = inputHeigh;
//        outputHeigh = inputHeigh;
//        outputTop = inputTop;
//         raise = inputHeigh/2 - inputWidth;
//        if(raise%2!=0)
//        {
//            outputWidth = inputWidth+(raise/2);
//            outputLeft = inputLeft-(raise/2)+1;
//        }
//        else
//        {
//            outputWidth = inputWidth+(raise/2);
//            outputLeft = inputLeft-(raise/2);
//        }
    }
    qDebug()<<"raise:"<<raise<<"\toutputWidth "<<outputWidth<<"\toutputLeft "<<outputLeft<<"\toutputHeigh "<<outputHeigh<<"\toutputTop "<<outputTop;
}
void ReadXML()
{
    //open xml file and read all content to QDomDocument
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug("cant oopen file");
    }
    if(!doc.setContent(&file))
    {
        qDebug("cant set content");
    }
    //close file after readed
    file.close();

    QDomElement  docElem = doc.documentElement();
    //get all node has tag name as box
    QDomNodeList nodeList = doc.elementsByTagName("box");
    for(int i=0; i<nodeList.size();i++)
    {
        //convert node to element to read attribute "width" and "heigh"
        QDomElement elem = nodeList.at(i).toElement();
        inputWidth = elem.attributeNode("width").value().toDouble();
        inputHeigh = elem.attribute("height").toDouble();
        inputTop = elem.attribute("top").toDouble();
        inputLeft = elem.attribute("left").toDouble();
        qDebug()<<"inputWidth "<<inputWidth<<"\tinputLeft "<<inputLeft<<"\tinputHeigh "<<inputHeigh<<"\tinputTop "<<inputTop;
//        setOutputValue();
        DisplayRatio();
        //set value to property
//        elem.setAttribute("width",outputWidth);
//        elem.setAttribute("height",outputHeigh);
//        elem.setAttribute("top",outputTop);
//        elem.setAttribute("left",outputLeft);
    }
//    SaveXML();
    qDebug()<<"minW: "<<minW << "minH: "<<minH<<" "<<minW*minH;
    qDebug()<<"minRatio: "<<minRatio<<"maxRatio: "<<maxRatio;
    qDebug()<<"minaread: "<<minArea;
}


int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    ReadXML();

    return 0;
}
