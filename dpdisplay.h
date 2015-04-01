#ifndef DPDISPLAY_H
#define DPDISPLAY_H

#include "editdistance.h"
#include "displaygrid.h"

class DPDisplay : public DisplayGrid
{
public:
    DPDisplay(EditDistance*, QWidget*);
    ~DPDisplay();

    EditDistance* get();
    void setManualTraceback(bool);
    void updateDisplay();

protected:
    void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;

private:
    void setup();

    bool manualTarceback;
    EditDistance* ed;

    int previousRow;
    int previousColumn;
};

#endif // DPDISPLAY_H
