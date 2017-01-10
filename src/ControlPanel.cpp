/**
 * Copyright (C) 2017 Braden Walters
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include "ControlPanel.hpp"

ControlPanel::ControlPanel(QWidget *parent) :
  QMainWindow(parent)
{
  // Set title and height.
  setWindowTitle("Sternenhimmel");
  setFixedSize(300, 350);

  // Create layout for form.
  auto formWidget = new QWidget();
  auto formLayout = new QFormLayout();
  formWidget->setLayout(formLayout);

  // Create pod URL field.
  podUrlEdit = new QPlainTextEdit();
  podUrlEdit->setMaximumHeight(TEXT_EDIT_HEIGHT);
  formLayout->addRow("Pod", podUrlEdit);

  // Create tag field.
  tagEdit = new QPlainTextEdit();
  tagEdit->setMaximumHeight(TEXT_EDIT_HEIGHT);
  formLayout->addRow("Tag", tagEdit);

  // Create connect button.
  auto connectButton = new QPushButton("Connect");
  connectButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
  formLayout->addWidget(connectButton);

  // Set up connect button signal.
  connect(connectButton, SIGNAL(released()), this, SLOT(startPresentation()));

  // Create main stacked widget to switch betweenconnected and disconnected
  // state.
  central = new QStackedWidget();
  central->addWidget(formWidget);

  // Set central widget with layout.
  setCentralWidget(central);
}

ControlPanel::~ControlPanel()
{
}

void ControlPanel::startPresentation()
{
  auto podUrl = podUrlEdit->toPlainText();
  auto tag = tagEdit->toPlainText();
  presentation = new Presentation(podUrl, tag, this);
  presentation->show();
}
