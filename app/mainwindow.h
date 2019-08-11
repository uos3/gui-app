#pragma once

#include "packet.h"
#include "db_columns.h"
#include "db_graph.h"
#include "db_table.h"

#include <QDockWidget>
#include <QListView>
#include <QListWidget>
#include <QMainWindow>
#include <QSplitter>
#include <QSqlDatabase>
#include <QTabWidget>

namespace {
	/* TODO #cleanup: get from elsewhere */
	static const std::string FRAMES_TABLE_NAME = "frames";
	static const std::string GPS_TABLE_NAME = "gps";
	static const std::string IMU_TABLE_NAME = "imu";
	static const std::string HEALTH_TABLE_NAME = "health";
	static const std::string IMG_TABLE_NAME = "img";
	static const std::string CONFIG_TABLE_NAME = "config";

	static const std::string FRAMES_TITLE = "Frames";
	static const std::string GPS_TITLE = "GPS";
	static const std::string IMU_TITLE = "IMU";
	static const std::string HEALTH_TITLE = "Health";
	static const std::string IMG_TITLE = "IMG";
	static const std::string CONFIG_TITLE = "Config";
}

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	explicit MainWindow(
		QSqlDatabase& db,
		QWidget *parent = nullptr,
		Qt::WindowFlags flags = Qt::WindowFlags());

public slots:
	void refresh (const Packet& p);

private:
	void setUpTables ();
	void setUpColumns ();
	void setUpGraphTabs ();

	DBGraph* addGraph ();
	void setActiveGraph (DBGraph* graph);

	static const int TAB_MARGINS = 5;

	QSqlDatabase& db;

	// tables in a top-level tab.
	DBTable frames_table;
	DBTable gps_table;
	DBTable imu_table;
	DBTable health_table;
	DBTable img_table;
	DBTable config_table;

	QTabWidget* tables_tabs;
	QWidget* tables_widget;
	QDockWidget* tables_dock;

	// checkable list of columns on the side of another top-level tab.
	// note: no 'frames' list, as none of the values in the 'frames' table are
	// graphable.
	QListView* gps_column_list;
	QListView* imu_column_list;
	QListView* health_column_list;
	QListView* img_column_list;
	QListView* config_column_list;

	QTabWidget* columns_tabs;

	// customisable graph(s) in the centre of the columns tab.
	std::vector<DBGraph*> graphs;
	QTabWidget* graph_tabs;

	QSplitter* graphing_split;
	QWidget* graphing_widget;
	QDockWidget* graphing_dock;
};
