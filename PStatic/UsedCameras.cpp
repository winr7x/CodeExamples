#include <QtCore/QThread>

#include "AbstractIpCamera.h"
#include "Scheduler.h"
#include "ScheduleModel.h"
#include "CameraObject.h"
#include "CameraWorker.h"

#include "UsedCameras.h"

constexpr int CHECK_CAMERA_CONNECTION_STATES_TIMEOUT = 30 * 1000;

UsedCameras::UsedCameras (QObject *parent)
	: QObject (parent)
	, checkCameraConnectionStatesTimer_ (new QTimer (this))
{
	checkCameraConnectionStatesTimer_->start (CHECK_CAMERA_CONNECTION_STATES_TIMEOUT);
}

UsedCameras::~UsedCameras()
{

}

int UsedCameras::count() const
{
	return cameras_.size ();
}

bool UsedCameras::contains (const QString &address) const
{
	return camera (address) != nullptr;
}

bool UsedCameras::isEmpty () const
{
	return cameras_.isEmpty ();
}

AbstractIpCamera *UsedCameras::camera (int index) const
{
	if (!isIndexCorrect (index)) {
		return nullptr;
	}

	return cameras_.at (index)->camera ();
}

UsedCameras::Cameras::const_iterator UsedCameras::find (const QString &address) const
{
	return std::find_if (cameras_.begin (), cameras_.end (),
	[address] (decltype (cameras_.front ()) camera) {
		return camera->camera ()->address () == address;
	});
}

AbstractIpCamera *UsedCameras::camera (const QString &address) const
{
	auto it = find (address);
	return (it == cameras_.end ()) ? nullptr : (*it)->camera ();
}

ScheduleModel *UsedCameras::scheduleModel (const QString &address) const
{
	auto it = find (address);
	return (it == cameras_.end ()) ? nullptr : (*it)->scheduleModel ();
}

void UsedCameras::addCamera (AbstractIpCamera *camera)
{
	QThread *cameraThread = new QThread;
	CameraObject *cameraObject = new CameraObject (camera);

	connect (checkCameraConnectionStatesTimer_,
			 SIGNAL (timeout ()),
			 cameraObject->camera (),
			 SLOT (checkConnectionState ()));

	cameraObject->camera ()->checkConnectionState ();

	connect (cameraThread, SIGNAL (started ()), cameraObject, SLOT (start ()));
	connect (cameraThread, SIGNAL (finished ()), cameraThread, SLOT (deleteLater ()));

	cameraObject->moveToThread (cameraThread);

	cameras_.push_back (cameraObject);
	cameraThreads_.push_back (cameraThread);

	cameraThread->start ();
}

void UsedCameras::removeCamera (int index)
{
	if (isIndexCorrect (index)) {
		CameraObject *camera = cameras_.at (index);
		Q_CHECK_PTR (camera);

		camera->stop ();
		camera->deleteLater ();
		cameras_.remove (index);

		QThread *thread = cameraThreads_.at (index);
		Q_CHECK_PTR (thread);

		thread->quit ();
		cameraThreads_.remove (index);
	}
}

bool UsedCameras::removeCamera (const QString &address)
{
	const auto it = std::find_if (cameras_.begin (), cameras_.end (),
	[address] (decltype (cameras_.front ()) camera) {
		return camera->camera ()->address () == address;
	});

	const bool result = (it != cameras_.end ());

	if (result) {
		removeCamera (cameras_.indexOf (*it));
	}

	return result;
}

void UsedCameras::clear()
{
	while (!cameras_.isEmpty ()) {
		removeCamera (0);
	}
}

void UsedCameras::updateLocations ()
{
	for (CameraObject *cameraObject : cameras_) {
		cameraObject->camera ()->updateLocations ();
	}
}

void UsedCameras::stopCameras()
{
	for (CameraObject *camera : cameras_) {
		QMetaObject::invokeMethod (camera, "stop");
	}
}

bool UsedCameras::isIndexCorrect (int index) const
{
	return (index >= 0) && (index < count ());
}
