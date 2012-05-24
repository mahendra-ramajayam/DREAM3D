/* ============================================================================
 * Copyright (c) 2012 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2012 Dr. Michael A. Groeber (US Air Force Research Laboratories)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Michael A. Groeber, Michael A. Jackson, the US Air Force,
 * BlueQuartz Software nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  This code was written under United States Air Force Contract number
 *                           FA8650-07-D-5800
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef _PipelineViewWidget_H
#define _PipelineViewWidget_H

#include <QtGui/QFrame>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QTextEdit>

#include "PipelineBuilder/QFilterWidget.h"


/*
 *
 */
class PipelineViewWidget : public QFrame
{
    Q_OBJECT;

  public:
    PipelineViewWidget(QWidget* parent = 0);
    virtual ~PipelineViewWidget();

    int filterCount();
    QFilterWidget* filterWidgetAt(int index);
    void clearWidgets();
    QFilterWidget* addFilter(QString filterName, int index =-1);
    void setErrorsTextArea(QTextEdit* t);

  public slots:
    void removeFilterWidget();
    void setSelectedFilterWidget(QFilterWidget* w);
    void setFilterBeingDragged(QFilterWidget* w);
    void preflightPipeline();

    // Slots for the pipeline to communicate back to us
  public slots:
    void preflightErrorMessage(const QString &str);


  signals:
     void addPlaceHolderFilter(QPoint p);
     void removePlaceHolderFilter();

  protected:
     void setupGui();
      void dragEnterEvent(QDragEnterEvent *event);
      void dragMoveEvent(QDragMoveEvent *event);
      void dropEvent(QDropEvent *event);
   //   void mousePressEvent(QMouseEvent *event);

  private:
    QFilterWidget*            m_SelectedFilterWidget;
    QVBoxLayout*              m_FilterWidgetLayout;
    QFilterWidget*            m_FilterBeingDragged;
    int                       m_DropIndex;
    QStringList               m_PipelineErrorList;
    QTextEdit*                m_ErrorsArea;

    PipelineViewWidget(const PipelineViewWidget&); // Copy Constructor Not Implemented
    void operator=(const PipelineViewWidget&); // Operator '=' Not Implemented
};

#endif /* _PipelineViewWidget_H */