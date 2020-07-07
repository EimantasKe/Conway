#include "conways.h"
#include <QFile>
#include <QTextStream>
#include <QRect>

//initialize empty board
Conway::Conway(QObject *parent) : QAbstractTableModel(parent){
    clear();
}

// return table height
int Conway::rowCount(const QModelIndex &parent) const{
    if (parent.isValid()){
        return 0;
    }else{
        return height;
    }
}

// returns table width
int Conway::columnCount(const QModelIndex &parent) const{
    if (parent.isValid()){
        return 0;
    }else{
        return width;
    }
}

// return current board
QVariant Conway::data(const QModelIndex &index, int role) const{
    if (!index.isValid() || role != CellRole){
        return QVariant();
    }else{
        return QVariant(m_currentState[cellIndex({index.column(), index.row()})]);
    }
}

// setData is necessary for AbstractTableModel
// Sets the role data for the item at index to value.
bool Conway::setData(const QModelIndex &index, const QVariant &value, int role){
    if (role != CellRole || data(index, role) == value){
        return false;
    }else{
        m_currentState[cellIndex({index.column(), index.row()})] = value.toBool();
        emit dataChanged(index, index, {role});
        return true;
    }
}

// flags function is necessary for AbstractTableModel but is never called because the program uses QML instead of widgets
// Returns the item flags for the given index.
Qt::ItemFlags Conway::flags(const QModelIndex &index) const{
    if (!index.isValid()){
        return Qt::NoItemFlags;
    }else{
        return Qt::ItemIsEditable;
    }
}

// initiates the next step
void Conway::nextStep(){
    StateContainer newValues;

    // calculate the new board
    for (std::size_t i = 0; i < size; ++i) {

        //check the value of the current cell
        bool currentState = m_currentState[i];

        // get the neighbour count for the current cell
        int cellNeighborsCount = this->cellNeighborsCount(cellCoordinatesFromIndex(static_cast<int>(i)));

        // the cells remains alive or dies depending on NeighbourCount
        newValues[i] = currentState == true
                ? cellNeighborsCount == 2 || cellNeighborsCount == 3
                : cellNeighborsCount == 3;
    }
    // replace the current board with the new board
    m_currentState = std::move(newValues);

    emit dataChanged(index(0, 0), index(height - 1, width - 1), {CellRole});
}

// sets all cells to false (clearing the board)
void Conway::clear(){
    m_currentState.fill(false);
    emit dataChanged(index(0, 0), index(height - 1, width - 1), {CellRole});
}

// counts the number of neighbours a cell has
int Conway::cellNeighborsCount(const QPoint &cellCoordinates) const{
    int count = 0;

    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            // skip the cell itself
            if (x == 0 && y == 0)
                continue;

            const QPoint neighborPosition { cellCoordinates.x() + x, cellCoordinates.y() + y };
            // check if any potential neighbours are out of bounds
            if (!areCellCoordinatesValid(neighborPosition))
                continue;

            // count the neighbours
            if (m_currentState[cellIndex(neighborPosition)])
                ++count;

            // there is no difference between 8 and 3 neighbours
            if (count > 3)
                return count;
        }
    }
    return count;
}

// check to see if given coordinates are within the board
bool Conway::areCellCoordinatesValid(const QPoint &coordinates){
    return QRect(0, 0, width, height).contains(coordinates);
}

// gets coordinates from the index
QPoint Conway::cellCoordinatesFromIndex(int cellIndex){
    return {cellIndex % width, cellIndex / width};
}

// gives the index position based on given coordinates
std::size_t Conway::cellIndex(const QPoint &coordinates){
    return std::size_t(coordinates.y() * width + coordinates.x());
}

