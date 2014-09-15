/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "filesystemmodel_p.h"
#include <QFileSystemModel>
#include <QDateTime>

class FileSystemModelPrivate
{

public:
    FileSystemModelPrivate(FileSystemModel *parent) :
        q_ptr(parent),
        model(new QFileSystemModel(parent)),
        filterPath("/")
    {
    }

    virtual ~FileSystemModelPrivate() {}
    
    void _q_onDirectoryLoaded(const QString &directory) {
        Q_Q(FileSystemModel);
        
        loadedDirectories.removeOne(directory);
        loadedDirectories.append(directory);
        emit q->directoryLoaded(directory);
    }

    FileSystemModel *q_ptr;

    QFileSystemModel *model;
    
    QString filterPath;
    
    QStringList loadedDirectories;

    Q_DECLARE_PUBLIC(FileSystemModel)
};

FileSystemModel::FileSystemModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    d_ptr(new FileSystemModelPrivate(this))
{
    Q_D(const FileSystemModel);

    this->setSourceModel(d->model);
    this->setFilterRole(FileNameRole);
    this->setDynamicSortFilter(true);
    this->connect(d->model, SIGNAL(rootPathChanged(QString)), this, SIGNAL(rootPathChanged()));
    this->connect(d->model, SIGNAL(directoryLoaded(QString)), this, SLOT(_q_onDirectoryLoaded(QString)));
}

FileSystemModel::FileSystemModel(FileSystemModelPrivate &dd, QObject *parent) :
    QSortFilterProxyModel(parent),
    d_ptr(&dd)
{
    Q_D(const FileSystemModel);

    this->setSourceModel(d->model);
    this->setFilterRole(FileNameRole);
    this->setDynamicSortFilter(true);
    this->connect(d->model, SIGNAL(rootPathChanged(QString)), this, SIGNAL(rootPathChanged()));
    this->connect(d->model, SIGNAL(directoryLoaded(QString)), this, SLOT(_q_onDirectoryLoaded(QString)));
}

FileSystemModel::~FileSystemModel() {}

QString FileSystemModel::rootPath() const {
    Q_D(const FileSystemModel);

    return d->model->rootPath();
}

void FileSystemModel::setRootPath(const QString &path) {
    Q_D(FileSystemModel);

    d->model->setRootPath(path);
}

QString FileSystemModel::filterPath() const {
    Q_D(const FileSystemModel);

    return d->filterPath;
}

void FileSystemModel::setFilterPath(const QString &path) {
    if (path != this->filterPath()) {
        Q_D(FileSystemModel);
        d->filterPath = path;
        emit filterPathChanged();
    }
}

bool FileSystemModel::showDirs() const {
    Q_D(const FileSystemModel);

    return d->model->filter().testFlag(QDir::Dirs);
}

void FileSystemModel::setShowDirs(bool show) {
    if (show != this->showDirs()) {
        Q_D(FileSystemModel);
        d->model->setFilter(show ? d->model->filter() |= QDir::Dirs : d->model->filter() &= ~QDir::Dirs);
        emit dirFilterChanged();
    }
}

bool FileSystemModel::showFiles() const {
    Q_D(const FileSystemModel);

    return d->model->filter().testFlag(QDir::Files);
}

void FileSystemModel::setShowFiles(bool show) {
    if (show != this->showFiles()) {
        Q_D(FileSystemModel);
        d->model->setFilter(show ? d->model->filter() |= QDir::Files : d->model->filter() &= ~QDir::Files);
        emit dirFilterChanged();
    }
}

bool FileSystemModel::showHidden() const {
    Q_D(const FileSystemModel);

    return d->model->filter().testFlag(QDir::Hidden);
}

void FileSystemModel::setShowHidden(bool show) {
    if (show != this->showHidden()) {
        Q_D(FileSystemModel);
        d->model->setFilter(show ? d->model->filter() |= QDir::Hidden : d->model->filter() &= ~QDir::Hidden);
    }
}

bool FileSystemModel::showDotAndDotDot() const {
    Q_D(const FileSystemModel);

    return (!d->model->filter().testFlag(QDir::NoDotAndDotDot));
}

void FileSystemModel::setShowDotAndDotDot(bool show) {
    if (show != this->showDotAndDotDot()) {
        Q_D(FileSystemModel);
        d->model->setFilter(show ? d->model->filter() &= ~QDir::NoDotAndDotDot : d->model->filter() |= QDir::NoDotAndDotDot);
        emit dirFilterChanged();
    }
}

bool FileSystemModel::showSymlinks() const {
    Q_D(const FileSystemModel);

    return !d->model->filter().testFlag(QDir::NoSymLinks);
}

void FileSystemModel::setShowSymlinks(bool show) {
    if (show != this->showSymlinks()) {
        Q_D(FileSystemModel);
        d->model->setFilter(show ? d->model->filter() &= ~QDir::NoSymLinks : d->model->filter() |= QDir::NoSymLinks);
        emit dirFilterChanged();
    }
}

bool FileSystemModel::resolveSymlinks() const {
    Q_D(const FileSystemModel);

    return d->model->resolveSymlinks();
}

void FileSystemModel::setResolveSymlinks(bool resolve) {
    if (resolve != this->resolveSymlinks()) {
        Q_D(FileSystemModel);
        d->model->setResolveSymlinks(resolve);
        emit resolveSymlinksChanged();
    }
}

bool FileSystemModel::isReadOnly() const {
    Q_D(const FileSystemModel);

    return d->model->isReadOnly();
}

void FileSystemModel::setReadOnly(bool ro) {
    if (ro != this->isReadOnly()) {
        Q_D(FileSystemModel);
        d->model->setReadOnly(ro);
        emit readOnlyChanged();
    }
}

bool FileSystemModel::nameFilterDisables() const {
    Q_D(const FileSystemModel);

    return d->model->nameFilterDisables();
}

void FileSystemModel::setNameFilterDisables(bool disables) {
    if (disables != this->nameFilterDisables()) {
        Q_D(FileSystemModel);
        d->model->setNameFilterDisables(disables);
        emit nameFilterDisablesChanged();
    }
}

QStringList FileSystemModel::nameFilters() const {
    Q_D(const FileSystemModel);

    return d->model->nameFilters();
}

void FileSystemModel::setNameFilters(const QStringList &filters) {
    Q_D(FileSystemModel);

    d->model->setNameFilters(filters);
    emit nameFiltersChanged();
}

QStringList FileSystemModel::loadedDirectories() const {
    Q_D(const FileSystemModel);
    
    return d->loadedDirectories;
}

bool FileSystemModel::directoryIsLoaded(const QString &directory) const {
    return this->loadedDirectories().contains(directory);
}

int FileSystemModel::count(const QModelIndex &parent) const {
    Q_D(const FileSystemModel);

    return d->model->rowCount(this->mapToSource(parent));
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const {
    return QSortFilterProxyModel::data(index, role);
}

bool FileSystemModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    return QSortFilterProxyModel::setData(index, value, role);
}

QModelIndex FileSystemModel::index(const QString &path, int column) const {
    Q_D(const FileSystemModel);

    return this->mapFromSource(d->model->index(path, column));
}

QString FileSystemModel::filePath(const QModelIndex &index) const {
    Q_D(const FileSystemModel);

    return d->model->filePath(this->mapToSource(index));
}

bool FileSystemModel::isDir(const QModelIndex &index) const {
    Q_D(const FileSystemModel);

    return d->model->isDir(this->mapToSource(index));
}

qint64 FileSystemModel::size(const QModelIndex &index) const {
    Q_D(const FileSystemModel);

    return d->model->size(this->mapToSource(index));
}

QString FileSystemModel::type(const QModelIndex &index) const {
    Q_D(const FileSystemModel);

    return d->model->type(this->mapToSource(index));
}

QDateTime FileSystemModel::lastModified(const QModelIndex &index) const {
    Q_D(const FileSystemModel);

    return d->model->lastModified(this->mapToSource(index));
}

QModelIndex FileSystemModel::mkdir(const QModelIndex &parent, const QString &name) {
    Q_D(FileSystemModel);

    return this->mapFromSource(d->model->mkdir(this->mapToSource(parent), name));
}

bool FileSystemModel::rmdir(const QModelIndex &index) const {
    Q_D(const FileSystemModel);

    return d->model->rmdir(this->mapToSource(index));
}

QString FileSystemModel::fileName(const QModelIndex &index) const {
    Q_D(const FileSystemModel);

    return d->model->fileName(this->mapToSource(index));
}

QString FileSystemModel::fileIcon(const QModelIndex &index) const {
    Q_D(const FileSystemModel);

    return d->model->fileIcon(this->mapToSource(index)).name();
}

bool FileSystemModel::remove(const QModelIndex &index) const {
    Q_D(const FileSystemModel);

    return d->model->remove(this->mapToSource(index));
}

bool FileSystemModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {
    Q_D(const FileSystemModel);
    
    if (source_parent == d->model->index(this->filterPath())) {
        return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    }

    return true;
}

#include "moc_filesystemmodel_p.cpp"
