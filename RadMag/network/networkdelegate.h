#ifndef NETWORKDELEGATE_H
#define NETWORKDELEGATE_H

#include <QByteArray>

class NetworkDelegate
{
public:
    NetworkDelegate();

    virtual void didReceiveData(QByteArray byteArrayReceived) = 0;
    virtual void didNotReceiveData(QString error) = 0;
};

#endif // NETWORKDELEGATE_H
