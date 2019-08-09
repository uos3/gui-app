#pragma once

#include "db_columns.h"
#include "db_table.h"

#include <QChart>
#include <QChartView>
#include <QDateTimeAxis>
#include <QMetaObject>
#include <QLineSeries>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QValueAxis>
#include <QWidget>

#include <map>
#include <utility>


class DBGraph : public QWidget {
	Q_OBJECT

public:
	DBGraph (
		QSqlDatabase& db, QWidget* parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());

	// add a table to be able to get lines from.
	void add_table (std::string table_name, DBColumns* columns);

	// remove a table.
	void remove_table (std::string table_name);

	// refresh the lines in th chart.
	void refresh ();

	// update which columns have a line in the chart.
	void update_lines (DBColumns* columns, std::string column_name);

private:
	// get a line in the chart from its name.
	// note: to get a properly formatted line name to put into this method, used
	// DBGraph::line_name.
	QtCharts::QLineSeries* get_line (std::string name) const;

	// regenerate the axes of the chart.
	void recreateAxes ();

	// get the name of a line in the chart.
	static std::string line_name (std::string table_name, std::string column_name);

	// get the database query used to retrieve the data for drawing lines.
	static std::string query_string (std::string table, std::string sort_by="");

	static const int margins = 0;

	QSqlDatabase& db;

	std::map<std::string, std::pair<DBColumns*, QSqlQueryModel*>> tables;

	/* TODO #speed: implement caching of previously shown lines and their data */
	QtCharts::QChart* chart;
	QtCharts::QChartView* view;
	QtCharts::QDateTimeAxis* x_axis;
	QtCharts::QValueAxis* y_axis;
};
