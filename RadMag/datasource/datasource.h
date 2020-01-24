#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QString>
#include <QStringList>

class DataSource
{
public:

    enum Resources {
        Play,
        Stop,
        Search,
        Star,
        StarBorder,
        Remove,
    };

    enum Filters {
        Name,
        Country,
        Language,
        Tag,
    };

    DataSource();

    QString static resource(Resources resourceString);
    QString static radioFiltered(Filters filter = DataSource::Name);
    Filters static typeOfFilter(QString filterName);
    QStringList static completionList();

private:
    static QString m_radioPath;
};

#endif // DATASOURCE_H
