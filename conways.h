#ifndef CONWAYS_H
#define CONWAYS_H

#include <array>
#include <QAbstractTableModel>
#include <QPoint>
#include <QtQml/qqml.h>

class Conway : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_ENUMS(Roles)

public:
    enum Roles {
        CellRole
    };

    QHash<int, QByteArray> roleNames() const override{
        return {
            {CellRole, "value"}
        };
    } explicit Conway(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // necessary for AbstractTableModel
    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    //Q_INVOKABLE should allow for C++ to be connected with QML
    Q_INVOKABLE void nextStep();
    Q_INVOKABLE void clear();

private:
    // defines size of the actual board
    static constexpr int width = 200;
    static constexpr int height = 200;
    static constexpr int size = width * height;

    // saving the states of cells
    using StateContainer = std::array<bool, size>;
    StateContainer m_currentState;

    int cellNeighborsCount(const QPoint &cellCoordinates) const;
    static bool areCellCoordinatesValid(const QPoint &coordinates);
    static QPoint cellCoordinatesFromIndex(int cellIndex);
    static std::size_t cellIndex(const QPoint &coordinates);
};

#endif // CONWAYS_H
