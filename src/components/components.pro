TEMPLATE = lib
CONFIG = qt plugin
QT += maemo5 declarative dbus

TARGET = hildoncomponents

HEADERS += \
    action_p.h \
    actiongroup_p.h \
    actiongroup_p_p.h \
    anchorline_p.h \
    anchors_p.h \
    anchors_p_p.h \
    button_p.h \
    button_p_p.h \
    buttonrow_p.h \
    buttonrow_p_p.h \
    checkbox_p.h \
    checkbox_p_p.h \
    column_p.h \
    column_p_p.h \
    dateselector_p.h \
    #delegateitem_p.h \
    #delegateitem_p_p.h \
    dialog_p.h \
    dialog_p_p.h \
    editbar_p.h \
    editbar_p_p.h \
    filedialog_p.h \
    filedialog_p_p.h \
    flickable_p.h \
    flickable_p_p.h \
    flow_p.h \
    flow_p_p.h \
    grid_p.h \
    grid_p_p.h \
    informationbox_p.h \
    informationbox_p_p.h \
    item_p.h \
    item_p_p.h \
    #itemdelegate_p.h \
    #itemdelegate_p_p.h \
    #itemdelegatetext_p.h \
    #itemdelegatetext_p_p.h \
    label_p.h \
    listselector_p.h \
    listselector_p_p.h \
    listview_p.h \
    listview_p_p.h \
    loader_p.h \
    loader_p_p.h \
    menu_p.h \
    menu_p_p.h \
    mousearea_p.h \
    mousearea_p_p.h \
    platformstyle_p.h \
    progressbar_p.h \
    progressbar_p_p.h \
    radiobutton_p.h \
    radiobutton_p_p.h \
    row_p.h \
    row_p_p.h \
    screen_p.h \
    screen_p_p.h \
    separator_p.h \
    slider_p.h \
    slider_p_p.h \
    spinbox_p.h \
    spinbox_p_p.h \
    tabgroup_p.h \
    tabgroup_p_p.h \
    text_p.h \
    text_p_p.h \
    textedit_p.h \
    textedit_p_p.h \
    textfield_p.h \
    textfield_p_p.h \
    timer_p.h \
    timer_p_p.h \
    timeselector_p.h \
    toolbar_p.h \
    toolbar_p_p.h \
    toolbutton_p.h \
    toolbutton_p_p.h \
    valuebutton_p.h \
    valuebutton_p_p.h \
    valueselector_p.h \
    valueselector_p_p.h \
    variantlistmodel_p.h \
    variantlistmodel_p_p.h \
    window_p.h \
    window_p_p.h \
    windowstack_p.h \
    windowstack_p_p.h \
    plugin_p.h

SOURCES += \
    action.cpp \
    actiongroup.cpp \
    anchors.cpp \
    button.cpp \
    buttonrow.cpp \
    checkbox.cpp \
    column.cpp \
    dateselector.cpp \
    #delegateitem.cpp \
    dialog.cpp \
    editbar.cpp \
    filedialog.cpp \
    flickable.cpp \
    flow.cpp \
    grid.cpp \
    informationbox.cpp \
    item.cpp \
    #itemdelegate.cpp \
    #itemdelegatetext.cpp \
    listselector.cpp \
    listview.cpp \
    loader.cpp \
    menu.cpp \
    mousearea.cpp \
    platformstyle.cpp \
    progressbar.cpp \
    radiobutton.cpp \
    row.cpp \
    screen.cpp \
    separator.cpp \
    slider.cpp \
    spinbox.cpp \
    tabgroup.cpp \
    text.cpp \
    textedit.cpp \
    textfield.cpp \
    timer.cpp \
    timeselector.cpp \
    toolbar.cpp \
    toolbutton.cpp \
    valuebutton.cpp \
    valueselector.cpp \
    variantlistmodel.cpp \
    window.cpp \
    windowstack.cpp \
    plugin.cpp

qdeclarativesources.files += \
    qml/qmldir \
    qml/ProgressDialog.qml \
    qml/QueryDialog.qml

qdeclarativesources.path = /opt/lib/qt4/imports/org/hildon/components
target.path = /opt/lib/qt4/imports/org/hildon/components

INSTALLS += qdeclarativesources target
