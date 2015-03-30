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
    void updateDisplay();

protected:
    void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;

private:
    void setup();
    EditDistance* ed;
};

#endif // DPDISPLAY_H
