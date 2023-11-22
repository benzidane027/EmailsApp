#ifndef MODEL_H
#define MODEL_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QtSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QString>
#include <QList>
#include <QDebug>

typedef QMap<QString, QString> Map;

QT_BEGIN_NAMESPACE
namespace Data
{
    class AbstractModel;
    class Database;
    class User;

}
QT_END_NAMESPACE

class Database
{

private:
    QSqlDatabase db;
    Database()
    {
        qDebug() << "one one";
        namespace fs = std::filesystem;
        fs::path Path = fs::current_path();
        std::string currentPath = Path.string();
        this->db = QSqlDatabase::addDatabase("QSQLITE", "conn01");
        this->db.setDatabaseName(QString::fromStdString(currentPath + "database/mydatabase.db"));
    }

public:
    static Database &getInstance()
    {
        static Database instance;
        return instance;
    }
    ~Database()
    {
        db.removeDatabase("conn01");
        this->db.close();
    }
    QSqlDatabase get_Db()
    {
        return this->db;
    }
};

class AbstractModel
{
    // abbstraction class
protected:
    bool has_beee_save;

    virtual Map &toJson();
    virtual bool save();
};

class User
{
private:
    QString id;
    QString first_name;
    QString last_name;
    QString email;
    QString password;
    User(Map &map)
    {
        this->id = "";
        this->first_name = map.value("first_name");
        this->last_name = map.value("last_name");
        this->email = map.value("email");
        this->password = map.value("password");
    }

public:
    bool has_beee_save;

    User(QSqlQuery &query)
    {
        // qDebug()<<query->isValid();
        this->id = query.value("id").toString();
        this->first_name = query.value("first_name").toString();
        this->last_name = query.value("last_name").toString();
        this->email = query.value("email").toString();
        this->password = query.value("password").toString();
    }

    Map &toJson()
    {
        Map *json = new Map;
        json->insert(QString::fromStdString("id"), this->id);
        json->insert(QString::fromStdString("first_name"), this->first_name);
        json->insert(QString::fromStdString("last_name"), this->last_name);
        json->insert(QString::fromStdString("email"), this->email);
        json->insert(QString::fromStdString("password"), this->password);
        return *json;
    }
    bool save()
    {

        Database &db = Database::getInstance();
        if (db.get_Db().open())
        {
            std::ostringstream oss;
            oss << "INSERT INTO User(first_name,last_name,email,password) VALUES('"
                << this->first_name.toStdString() << "','"
                << this->last_name.toStdString() << "','"
                << this->email.toStdString() << "','"
                << this->password.toStdString() << "'"
                << ");";
            db.get_Db().exec(QString::fromStdString(oss.str()));
            this->has_beee_save = true;

        }

        return this->has_beee_save;
    }
    static User &fromJson(Map &data)
    {
        User *user = new User(data);
        return *user;
    }
    friend QDebug operator<<(QDebug os, const User &u)
    {
          os <<"\n";
          os << "id \t\t:" << u.id << "\n";
          os << "email \t\t:" << u.email << "\n";
          os << "first name \t:" << u.first_name << "\n";
          os << "last name \t:" << u.last_name << "\n";
          os << "password \t:" << u.password << "\n";
          return os;
           }

    friend std::ostream &operator<<(std::ostream &os, User &u)
    {
        os << u.first_name.toStdString();
        return os;
    }
};


#endif
