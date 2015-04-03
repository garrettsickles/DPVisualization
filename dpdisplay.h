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
    void setManualTraceback(bool);

    QString getToolTipText(int, int);

protected:
    void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *) Q_DECL_OVERRIDE;

private:
    bool manualTarceback;
    EditDistance* ed;

    int previousRow;
    int previousColumn;
};

#endif // DPDISPLAY_H
