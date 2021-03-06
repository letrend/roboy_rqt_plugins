#pragma once

#ifndef Q_MOC_RUN

#include <ros/ros.h>
#include <rqt_gui_cpp/plugin.h>
#include <roboy_motor_record/ui_roboy_motor_record.h>
#include <roboy_middleware_msgs/MotorStatus.h>
#include <roboy_middleware_msgs/MotorCommand.h>
#include <roboy_middleware_msgs/ADCvalue.h>
#include <QWidget>
#include <QFileDialog>
#include <QtQuick/QQuickView>
#include <pluginlib/class_list_macros.h>
#include <QStringList>
#include <QSlider>
#include <QLineEdit>
#include <QScrollArea>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QLabel>
#include <map>
#include <common_utilities/CommonDefinitions.h>
#include <std_srvs/SetBool.h>
#include <std_msgs/Float32.h>
#include <time.h>
#include <mutex>
#include <chrono>
#include <fstream>

#endif

using namespace std;
using namespace chrono;

class RoboyMotorRecord
        : public rqt_gui_cpp::Plugin {
    Q_OBJECT
public:
    RoboyMotorRecord();

    virtual void initPlugin(qt_gui_cpp::PluginContext &context);

    virtual void shutdownPlugin();

    virtual void saveSettings(qt_gui_cpp::Settings &plugin_settings,
                              qt_gui_cpp::Settings &instance_settings) const;

    virtual void restoreSettings(const qt_gui_cpp::Settings &plugin_settings,
                                 const qt_gui_cpp::Settings &instance_settings);
public Q_SLOTS:
    void record(bool checked);
    void motors();
    void time_span();
    void control_mode();
    void plotData();
private:
    void MotorStatus(const roboy_middleware_msgs::MotorStatus::ConstPtr &msg);
    void TestRigRelativePosition(const std_msgs::Float32::ConstPtr &msg);
    void TestRigWeight(const roboy_middleware_msgs::ADCvalue::ConstPtr &msg);
    Q_SIGNALS:
    void newData();
private:
    Ui::RoboyMotorRecord ui;
    QWidget *widget_;

    QVector<double> time;
    vector<int> motorIDs = {0};
    int cm = 0;
    int sample = 0;
    int sample_rate = 200;
    int ts = 5000; // time_span in ms
    high_resolution_clock::time_point start_time;
    bool recording = false;
    QVector<double> motorData[NUMBER_OF_FPGAS][NUMBER_OF_MOTORS_PER_FPGA][9];
    float test_rig_pos = 0, test_rig_weight = 0;
    QColor color_pallette[21] = {Qt::blue, Qt::red, Qt::green, Qt::cyan, Qt::magenta, Qt::darkGray, Qt::darkRed, Qt::darkGreen,
                                 Qt::darkBlue, Qt::darkCyan, Qt::darkMagenta, Qt::darkYellow, Qt::black, Qt::gray, Qt::green, Qt::cyan,
                                 Qt::blue, Qt::red, Qt::green, Qt::cyan, Qt::magenta};
    ros::NodeHandlePtr nh;
    ros::Subscriber motorStatus, testRigPosition, testRigWeight;
    ros::Publisher motorCommand;
    boost::shared_ptr<ros::AsyncSpinner> spinner;
    ofstream file;
    mutex mux;
};
