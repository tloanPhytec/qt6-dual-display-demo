#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Get screens
    QList<QScreen *> screens = QGuiApplication::screens();
    qDebug() << "Available screens:";
    for (int i = 0; i < screens.size(); ++i)
        qDebug() << i << ":" << screens[i]->name();

    // Load and show a QML window for each screen
    for (int i = 0; i < screens.size(); ++i) {
        QQmlApplicationEngine *perScreenEngine = new QQmlApplicationEngine();

        // Pass screen name to QML
        perScreenEngine->rootContext()->setContextProperty("screenName", screens[i]->name());

        const QUrl url(QStringLiteral("qrc:/test/main.qml"));
        QObject::connect(
            perScreenEngine,
            &QQmlApplicationEngine::objectCreated,
            &app,
            [url, screens, i](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);

                QQuickWindow *window = qobject_cast<QQuickWindow *>(obj);
                if (window) {
                    window->setScreen(screens[i]);
                    window->showFullScreen();
                }
            },
            Qt::QueuedConnection);

        perScreenEngine->load(url);
    }

    return app.exec();
}
