/* ============================================================================
 * Copyright (c) 2012 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2012 Dr. Michael A. Groeber (US Air Force Research Laboratories)
 * Copyright (c) 2012 Joseph B. Kleingers (Intern, University of Dayton)
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

#ifndef _DREAM3DHelpUrlGenerator_H
#define _DREAM3DHelpUrlGenerator_H

#include <QtCore/QUrl>
#include <QtCore/QString>

#include <QtGui/QApplication>


/**
 * @brief The DREAM3DHelpUrlGenerator class generates a QUrl that contains a path to the specified help file
 */
class DREAM3DHelpUrlGenerator
{

public:
  DREAM3DHelpUrlGenerator();
  virtual ~DREAM3DHelpUrlGenerator();

  /**
     * @brief Generates a help URL from the given lowercase name.
     */
  static QUrl generateHTMLUrl(QString helpName);

  /**
     * @brief Opens the URL specified in a web browser.  The variable "parent" is needed
   * to pop-up a dialog box if the opening process fails.
     */
  static void openHTMLUrl(QUrl URL, QWidget* parent);

  /**
     * @brief This function both generates a URL and opens it in a browser.  It is simply
   * a combination of the two previous functions, for convenience.
     */
  static void generateAndOpenHTMLUrl(QString helpName, QWidget* parent);

private:

  DREAM3DHelpUrlGenerator(const DREAM3DHelpUrlGenerator&); // Copy Constructor Not Implemented
  void operator=(const DREAM3DHelpUrlGenerator&); // Operator '=' Not Implemented
};

#endif /* _DREAM3DHelpUrlGenerator_H */
