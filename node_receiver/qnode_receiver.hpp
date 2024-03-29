#ifndef human_cognition_QNODE_RECEIVER_HPP_
#define human_cognition_QNODE_RECEIVER_HPP_

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#include "../node_common/qnode.hpp"
#endif

/*! \brief Specialized node class for receiving UDP packets
 * @author Christian Benz <zneb_naitsirhc@web.de>
 * @author Christoph Döringer <christoph.doeringer@gmail.com>
 * @author Hendrik Pfeifer <hendrikpfeifer@gmail.com>
 * @author Heiko Reinemuth <heiko.reinemuth@gmail.com>
 */
class QNodeReceiver: public QNode {

public:
	QNodeReceiver(int argc, char** argv);
	virtual ~QNodeReceiver() {
	}

	/***********************************************
	 IMPLEMENTATION OF PURE VIRTUAL METHODS
	 ***********************************************/
	bool readyForAction();
	void startAction();
	void stopAction();
	void run();

	/***********************************************
	 GETTER
	 ***********************************************/
	virtual QString getAssignAddress();
	virtual QString getIgnoreAddress();
	virtual QString getFrameAddress(const int &frame_index);
	virtual int getFrameHertzToDisplay(const int &frame_index);

	/***********************************************
	 SETTER
	 ***********************************************/
	virtual void addFrameAddress(QString address);
	virtual void setFrameAddress(const int &frame_index, QString address);
	virtual void setSignalResetModel(const bool &boolean);
	virtual void setSignalPerformance(const bool &boolean);
	virtual void setSignalEuler(const bool &boolean);
	virtual void setFrameEuler(const int &frame_index);
	virtual void setSignalInactivity(const bool &boolean);
	virtual void setSignalAsync(const bool &boolean);
	virtual void setValueAsync(const int &value);

private:
	/***********************************************
	 PRIVATE HELPER METHODS
	 ***********************************************/
	bool socketReady();
	bool socketCreation();
	bool socketOption();
	bool socketBinding();
	void initEuler();
	void initMessages();
	void initFrameRotation();
	void initFrameData();
	void displayFrameEuler();
	void displayFrameInactivity();
	void displayFrameAsync();

	//socket and address variables
	int udpSocket;
	int udpSocketBinding;
	int udpSocketOption;
	struct sockaddr_in socketAddress;
	struct sockaddr_in sensorAddress;
	socklen_t sensorAddressLength;
	SensorData sensorPacketData;
	int sensorPacketSize;

	//address placeholders
	QString stdAssignAddress;
	QString stdIgnoreAddress;

	//settings variables
	bool signalPerformance;
	bool signalEuler;
	int frameEuler;
	bool signalInactivity;
	bool signalAsync;
	int valueAsync;
	bool signalResetModel;

	//euler angle variables
	double frameEulerX;
	double frameEulerY;
	double frameEulerZ;

	//list of frame ip addresses
	QStringList frameAddressList;

	//current count of frame updates
	int frameUpdateCount[NUMBER_OF_FRAMES];

	//total count of frame updates in one second
	int frameHertzToDisplay[NUMBER_OF_FRAMES];

	//last frame message stamp
	ros::Time frameLastMsgStamp[NUMBER_OF_FRAMES];

	//time between the latest and the last frame message stamp in seconds
	int frameAsynchSpanSec[NUMBER_OF_FRAMES];

	//time between the latest and the last frame message stamp in nanoseconds
	int frameAsynchSpanNsec[NUMBER_OF_FRAMES];

	//urdf data model
	urdf::Model model;

	//base connector rotation
	tf::Quaternion tfBaseRot;

	//base connector message
	tf::StampedTransform tfBaseMsg;

	//frame rotation
	tf::Quaternion tfFrameRot[NUMBER_OF_FRAMES];

	//frame message
	tf::StampedTransform tfFrameMsg[NUMBER_OF_FRAMES];
};

#endif
