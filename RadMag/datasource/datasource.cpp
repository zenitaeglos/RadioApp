#include "datasource.h"

DataSource::DataSource()
{

}

QString DataSource::resource(DataSource::Resources resourceString)
{
    switch (resourceString) {
    case Play:
        return "://resources/baseline-play_circle_outline-24px.svg";
    case Stop:
        return "://resources/baseline-stop-24px.svg";
    case Search:
        return "://resources/baseline-search-24px.svg";
    default:
        return QString();
    }
}

QString DataSource::radioFiltered(DataSource::Filters filter)
{
    QString radioPath = "http://www.radio-browser.info/webservice/json/stations/";
    switch (filter) {
        case Name:
        return radioPath + "byname/";
    }
}
