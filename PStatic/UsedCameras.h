#pragma once

#include <QtCore/QObject>
#include <QtCore/QVector>

#include <QtNetwork/QHostAddress>

class AbstractIpCamera;
class CameraObject;
class CameraWorker;
class ScheduleModel;
class Scheduler;

/**
 * @class UsedCameras
 * @brief Класс, моделирующий список используемых камер
 */
class UsedCameras : public QObject
{
	Q_OBJECT

public:
	explicit UsedCameras (QObject *parent = nullptr);
	virtual ~UsedCameras ();

	/**
	 * @brief Показывает, пуст ли список
	 * @return true - если список пуст, false - если список не пуст
	 */
	bool isEmpty () const;

	/**
	 * @brief count Возвращает кол-во камер в списке
	 */
	int count () const;

	/**
	 * @brief Показывает, содержится ли в списке данная камера
	 * @param address IP-адрес камеры
	 * @return true - если содержится, false - если не содержится
	 */
	bool contains (const QString &address) const;

	/**
	 * @brief Предоставляет доступ к камере
	 * @param index индекс камеры
	 * @return указатель на камеру, если таковая была найдена в списке, nullptr - в противном случае
	 */
	AbstractIpCamera *camera (int index) const;

	/**
	 * @brief Предоставляет доступ к камере
	 * @param address IP-адрес камеры
	 * @return указатель на камеру, если таковая была найдена в списке, nullptr - в противном случае
	 */
	AbstractIpCamera *camera (const QString &address) const;

	/**
	 * @brief Предоставляет доступ к расписанию движения камеры по маршруту
	 * @param address IP-адрес камеры
	 * @return указатель на модель расписания движения камеры,
	 * если эта камера была найдена в списке, nullptr - в противном случае
	 */
	ScheduleModel *scheduleModel (const QString &address) const;

	/**
	 * @brief Добавляет камеру в список
	 * @param camera камера
	 */
	void addCamera (AbstractIpCamera *camera);

	/**
	 * @brief Удаляет камеру из списка
	 * @param address IP-адрес камеры
	 * @return true - если камера успешно удалена, false - в противном случае
	 */
	bool removeCamera (const QString &address);

	/**
	 * @brief Очищает список
	 */
	void clear ();

	/**
	 * @brief Обновляет таблицу местоположений
	 */
	void updateLocations ();

	/**
	 * @brief Останавливает работу камер
	 */
	void stopCameras ();

private:
	typedef QVector<CameraObject *> Cameras;
	typedef QVector<QThread *> CameraThreads;

private:
	Q_DISABLE_COPY (UsedCameras)

	bool isIndexCorrect (int index) const;
	void removeCamera (int index);

	Cameras::const_iterator find (const QString &address) const;

private:
	Cameras cameras_;
	CameraThreads cameraThreads_;

	class QTimer *checkCameraConnectionStatesTimer_;
};
