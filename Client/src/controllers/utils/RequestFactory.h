#ifndef REQUEST_FACTORY_H
#define REQUEST_FACTORY_H

#include <QJsonObject>
#include <QString>
#include <QDateTime>
#include <QJsonDocument>

namespace RequestFactory
{   
    // Auth requests
    inline QByteArray createLoginRequest(const QString &username, const QString &password)
    {
        QJsonObject request = {
            {"type", "LOGIN_REQUEST"},
            {"timestamp", QDateTime::currentSecsSinceEpoch()},
            {"payload", QJsonObject{
                            {"username", username},
                            {"password", password}}}};
        return QJsonDocument(request).toJson(QJsonDocument::Compact) + '\n';
    }

    inline QByteArray createRegisterRequest(const QString &username, const QString &password)
    {
        QJsonObject request = {
            {"type", "REGISTER_REQUEST"},
            {"timestamp", QDateTime::currentSecsSinceEpoch()},
            {"payload", QJsonObject{
                            {"username", username},
                            {"password", password}}}};
        return QJsonDocument(request).toJson(QJsonDocument::Compact) + '\n';
    }

    // Contacts requests
    inline QByteArray createSendFriendRequest(const QString &from, const QString &to)
    {
        QJsonObject request = {
            {"type", "SEND_FRIEND_REQUEST"},
            {"timestamp", QDateTime::currentSecsSinceEpoch()},
            {"payload", QJsonObject{
                            {"from", from},
                            {"to", to}}}};
        return QJsonDocument(request).toJson(QJsonDocument::Compact) + '\n';
    }

    inline QByteArray createCancelFriendRequest(const QString &from, const QString &to)
    {
        QJsonObject request = {
            {"type", "CANCEL_FRIEND_REQUEST"},
            {"timestamp", QDateTime::currentSecsSinceEpoch()},
            {"payload", QJsonObject{
                            {"from", from},
                            {"to", to}}}};
        return QJsonDocument(request).toJson(QJsonDocument::Compact) + '\n';
    }

    inline QByteArray createResponseFriendRequest(const QString &from, const QString &to, bool accept)
    {
        QJsonObject request = {
            {"type", "RESPOND_TO_FRIEND_REQUEST"},
            {"timestamp", QDateTime::currentSecsSinceEpoch()},
            {"payload", QJsonObject{
                            {"from", from},
                            {"to", to},
                            {"accept", accept}}}};
        return QJsonDocument(request).toJson(QJsonDocument::Compact) + '\n';
    }

    inline QByteArray createDeleteFriendRequest(const QString &from, const QString &to)
    {
        QJsonObject request = {
            {"type", "DELETE_FRIEND_REQUEST"},
            {"timestamp", QDateTime::currentSecsSinceEpoch()},
            {"payload", QJsonObject{
                            {"from", from},
                            {"to", to}}}};
        return QJsonDocument(request).toJson(QJsonDocument::Compact) + '\n';
    }

    inline QByteArray createFetchFriendsListRequest()
    {
        QJsonObject request = {
            {"type", "FETCH_FRIENDS_LIST_REQUEST"},
            {"timestamp", QDateTime::currentSecsSinceEpoch()},
            {"payload", QJsonObject{}}};
        return QJsonDocument(request).toJson(QJsonDocument::Compact) + '\n';
    }

    // Messages requests

}

#endif // REQUEST_FACTORY_H
