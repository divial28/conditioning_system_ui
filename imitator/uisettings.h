#ifndef UISETTINGS_H
#define UISETTINGS_H

#include <QWidget>

/* UISettings just contains slider handle static size
 * This is the only solution i found and it must be change if possible
 */
class UISettings
{
public:
    UISettings();

public:
    static int SliderHandleSize;
};

#endif // UISETTINGS_H
