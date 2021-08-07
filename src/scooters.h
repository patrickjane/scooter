// **************************************************************************
// class Scooters
// 02.07.2021
// Controller class/bridge between providers & QML
// **************************************************************************
// MIT License
// Copyright © 2021 Patrick Fial
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
// files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
// is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// **************************************************************************
// includes
// **************************************************************************

#ifndef SCOOTERS_H
#define SCOOTERS_H

#include <QObject>
#include <QDebug>
#include <QVariantList>
#include <QJSValue>
#include <QJSEngine>

#include "types.hpp"
#include "network.h"
#include "logger.h"

class QGeoPositionInfoSource;

// **************************************************************************
// namespace scooter
// **************************************************************************

namespace scooter
{
   // **************************************************************************
   // forwards
   // **************************************************************************

   class Provider;

   // **************************************************************************
   // class Scooters
   // **************************************************************************

   class Scooters : public Logger
   {
      Q_OBJECT
      Q_PROPERTY(QVariantList scooters READ getScooters NOTIFY scootersChanged)
      Q_PROPERTY(QVariant activeRide READ getActiveRide NOTIFY activeRideChanged)

      public:
         explicit Scooters(QObject* parent = nullptr);
         ~Scooters();

         // account

         Q_INVOKABLE void login(QString providerName, QString loginId, QString password = "");
         Q_INVOKABLE void logout(QString providerName);
         Q_INVOKABLE void confirmLogin(QString providerName, QString confirmation);
         Q_INVOKABLE void getProfile(QString providerName);

         // map

         Q_INVOKABLE void reloadScooters(QGeoCoordinate coordinates, int radius);
         const QVariantList& getScooters() const { return guiScooters; }
         Q_INVOKABLE void reloadAreas(QGeoCoordinate coordinates, int radius);

         // ride

         Q_INVOKABLE void ringScooter(QString providerName, QString id, QGeoCoordinate coordinate);
         Q_INVOKABLE void scanScooter(QString providerName, QString id, QGeoCoordinate coordinates);
         Q_INVOKABLE void startRide(QString providerName, QString unlockId, QGeoCoordinate coordinate);
         Q_INVOKABLE void stopRide(QGeoCoordinate coordinate);

         // information retrieval

         Q_INVOKABLE bool isLoggedIn(QString providerName);
         Q_INVOKABLE QString getAccountId(QString providerName);
         Q_INVOKABLE QVariant getActiveRide() { return activeRide ? QVariant(*activeRide) : QVariant(); }
         Q_INVOKABLE QVariantList getSupportedProviders() { return providerNames; }

      signals:

         // communication
         void notify(QString providerName, QString title, QString message);
         void error(QString providerName, QString error);
         void networkError(QString type, int code, QString error);
         void logMessage(QString provider, QString severity, QString message);

         // providers
         void ready();
         void scootersChanged(const QVariantList& scooters);
         void areasChanged(QString provider, QVariantList areas);
         void scooterScanned(QVariant scooter);
         void confirmLoginNeeded(QString providerName);
         void loginStatusChanged(QString providerName, bool loggedIn, QString account);
         void profile(QString providerName, QVariantMap profile);

         void activeRideChanged(QVariant ride, QString error, QString rideInfo);

      private:
         QVariantList guiScooters;
         ScooterRegistry scooterRegistry;
         network::Network net;
         ActiveRide* activeRide;

         QGeoPositionInfoSource* position;

         // providers

         QMap<QString, Provider*> providers;
         QVariantList providerNames;

         // QJSValue

         QJSEngine qjsEngine;
   };
}

#endif // SCOOTERS_H
