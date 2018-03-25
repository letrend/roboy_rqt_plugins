#pragma once

#ifndef Q_MOC_RUN

#include <ros/ros.h>
#include <rqt_gui_cpp/plugin.h>
#include <roboy_trajectories_control/ui_roboy_trajectories_control.h>
#include <QWidget>
#include <QtQuick/QQuickView>
#include <pluginlib/class_list_macros.h>
#include <QStringList>
#include <QSlider>
#include <QLineEdit>
#include <QScrollArea>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLabel>
#include <QListWidget>
#include <map>
#include <common_utilities/CommonDefinitions.h>
#include <common_utilities/MotorConfig.hpp>
#include <std_srvs/SetBool.h>

#endif

using namespace std;

class RoboyTrajectoriesControl:
        public rqt_gui_cpp::Plugin, MotorConfig {
        Q_OBJECT
        public:
            RoboyTrajectoriesControl();

            virtual void initPlugin(qt_gui_cpp::PluginContext &context);

            virtual void shutdownPlugin();

            virtual void saveSettings(qt_gui_cpp::Settings &plugin_settings,
                                      qt_gui_cpp::Settings &instance_settings) const;

            virtual void restoreSettings(const qt_gui_cpp::Settings &plugin_settings,
                                         const qt_gui_cpp::Settings &instance_settings);
        public Q_SLOTS:
            void onExistingTrajectoriesItemClicked(QListWidgetItem* item);
            void checkMotorStatus();
            void pullExistingTrajectories();
//            void stopButtonAllClicked();
//            void setPointChanged();
//            void setPointChangedSlider();
//            void setPointAllChanged();
//            void setPointAllChangedSlider();
//            void controlModeChanged();
//            void update_config();
//            void loadMotorConfig();
        private:
            Ui::RoboyTrajectoriesControl ui;
            QWidget *widget_;
            ros::NodeHandlePtr nh;
            ros::Publisher motorCommand;
            ros::ServiceClient motorControl, motorConfig, emergencyStop;
        private:
            bool stopButton;
            vector<double> setpoint;
            vector<int> control_mode;
            int total_number_of_motors = 0, number_of_fpgas = 1;
            vector<QRadioButton*> pos, vel, dis, force;
            vector<QSlider*> setpoint_slider_widget;
            vector<QLineEdit*> setpoint_widget;
            QLineEdit* scale;
};