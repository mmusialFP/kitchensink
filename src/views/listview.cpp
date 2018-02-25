/**********************************************************************
*
* Copyright (c) 2012-2018 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "listview.h"

#include <QAbstractItemModel>
#include <QListView>
#include <QModelIndex>
#include <QStringListModel>

ListView::ListView(QWidget *parent)
   : QWidget(parent), ui(new Ui::ListView)
{
   ui->setupUi(this);
   setWindowTitle("List View Model");

   QStringListModel *model = new QStringListModel(this);
   model->setStringList( getData() );

   //
   m_proxyModel = new QSortFilterProxyModel(this);
   m_proxyModel->setSourceModel(model);
   m_proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
   m_proxyModel->sort(0, Qt::AscendingOrder);
   m_proxyModel->setDynamicSortFilter(true);

   //
   ui->listView->setModel(m_proxyModel);
   ui->listView->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);

   // adjust the size
   QSize size = this->size();
   this->setMinimumHeight( size.height() );

   connect(ui->insert_PB,  &QAbstractButton::clicked, this, &ListView::addRow);
   connect(ui->delete_PB,  &QAbstractButton::clicked, this, &ListView::delRow);
}

ListView::~ListView()
{
   delete ui;
}

QStringList ListView::getData()
{
   QStringList data;

   data << "gallon" << "ounce" << "pinch" << "pound" << "cup"
        << "pint" << "quart" << "tsp" << "Tbsp" << "bunch" << "jigger" ;

   return data;
}

void ListView::addRow()
{
   // sort off
   m_proxyModel->setDynamicSortFilter(false);
   m_proxyModel->sort(-1);

   int row = ui->listView->currentIndex().row();
   m_proxyModel->insertRows(row,1);

   // get index
   QModelIndex index = m_proxyModel->index(row, 0);
   //    m_proxyModel->setData(index, QVariant("NEW"), Qt::EditRole);

   // select and edit
   ui->listView->setCurrentIndex(index);
   ui->listView->edit(index);

   // sort on
   m_proxyModel->setDynamicSortFilter(true);
   m_proxyModel->sort(0, Qt::AscendingOrder);
}

void ListView::delRow()
{
   m_proxyModel->removeRows(ui->listView->currentIndex().row(), 1);
}



