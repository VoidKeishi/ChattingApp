#include "ContactRepository.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

ContactRepository::ContactRepository(DatabaseManager* db) : db(db) {}

bool ContactRepository::createFriendRequest(const QString& from, const QString& to) {
    QSqlQuery query(db->database());
    query.prepare("INSERT INTO friend_requests (from_user, to_user) VALUES (?, ?)");
    query.addBindValue(from);
    query.addBindValue(to);
    return query.exec();
}

bool ContactRepository::updateRequestStatus(const QString& from, const QString& to, const QString& status) {
    db->database().transaction();
    
    QSqlQuery query(db->database());
    query.prepare("UPDATE friend_requests SET status = ? WHERE from_user = ? AND to_user = ?");
    query.addBindValue(status);
    query.addBindValue(from);
    query.addBindValue(to);
    
    if (!query.exec()) {
        db->database().rollback();
        return false;
    }

    if (status == "accepted") {
        query.prepare("INSERT INTO friends (user1, user2) VALUES (?, ?)");
        query.addBindValue(from);
        query.addBindValue(to);
        if (!query.exec()) {
            db->database().rollback();
            return false;
        }
    }

    return db->database().commit();
}

QVector<QString> ContactRepository::getFriendList(const QString& username) {
    QVector<QString> friends;
    QSqlQuery query(db->database());
    query.prepare(
        "SELECT user2 FROM friends WHERE user1 = ? "
        "UNION "
        "SELECT user1 FROM friends WHERE user2 = ?"
    );
    query.addBindValue(username);
    query.addBindValue(username);
    
    if (query.exec()) {
        while (query.next()) {
            friends.append(query.value(0).toString());
        }
    }
    return friends;
}

QVector<QPair<QString, QString>> ContactRepository::getPendingRequests(const QString& username) {
    QVector<QPair<QString, QString>> requests;
    QSqlQuery query(db->database());
    query.prepare("SELECT from_user, to_user FROM friend_requests WHERE to_user = ? AND status = 'pending'");
    query.addBindValue(username);
    
    if (query.exec()) {
        while (query.next()) {
            requests.append({query.value(0).toString(), query.value(1).toString()});
        }
    }
    return requests;
}

bool ContactRepository::areFriends(const QString& user1, const QString& user2) {
    QSqlQuery query(db->database());
    query.prepare(
        "SELECT COUNT(*) FROM friends WHERE "
        "(user1 = ? AND user2 = ?) OR (user1 = ? AND user2 = ?)"
    );
    query.addBindValue(user1);
    query.addBindValue(user2);
    query.addBindValue(user2);
    query.addBindValue(user1);
    
    return query.exec() && query.next() && query.value(0).toInt() > 0;
}