QT = core sql

CONFIG += c++17 cmdline console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        auth/authmenu.cpp \
        auth/register.cpp \
        cart/cart.cpp \
        auth/login.cpp \
    cart/stock.cpp \
        main.cpp \
        cart/productlist.cpp \
        profile/profilemenu.cpp \
        db/psql.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    auth/authmenu.h \
    auth/register.h \
    cart/cart.h \
    auth/login.h \
    cart/productlist.h \
    cart/stock.h \
    profile/profilemenu.h \
    db/psql.h \
    user.h
