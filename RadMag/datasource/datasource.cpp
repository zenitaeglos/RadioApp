#include "datasource.h"

QString DataSource::m_radioPath = "http://www.radio-browser.info/webservice/json/stations/";

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
    case Star:
        return "://resources/baseline-star-24px.svg";
    case StarBorder:
        return "://resources/baseline-star_border-24px.svg";
    case Remove:
        return "://resources/baseline-remove_circle_outline-24px.svg";
    default:
        return QString();
    }
}

QString DataSource::radioFiltered(DataSource::Filters filter /*= DataSource::Name*/)
{
    switch (filter) {
    case Name:
        return m_radioPath + "byname/";
    case Country:
        return m_radioPath + "bycountry/";
    case Language:
        return m_radioPath + "bylanguage/";
    case Tag:
        return m_radioPath + "bytag/";
    }
}

DataSource::Filters DataSource::typeOfFilter(QString filterName)
{
    if (filterName.toLower() == "country")
        return DataSource::Country;
    else if (filterName.toLower() == "language")
        return DataSource::Language;
    else if (filterName.toLower() == "tag")
        return DataSource::Tag;
    else
        return DataSource::Name;
}
