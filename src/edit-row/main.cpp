//
// Copyright (C) 2019 Rasmus Bonnedal
//

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <gtkmm.h>
#pragma GCC diagnostic pop

#include <iostream>

#include "treeview_enable_edit_next_field.h"
#include "treeview_enable_valid.h"

class MyTreeView : public Gtk::TreeView {
public:
    MyTreeView() {
        m_treeModel = Gtk::ListStore::create(m_columns);
        m_treeView.set_model(m_treeModel);
        m_treeView.append_column_editable("Id", m_columns.m_col_id);
        enableNumericColumnWithValid(m_treeView.get_column(0),
                                     m_columns.m_col_id,
                                     m_columns.m_col_id_valid);
        // This column is only shown for debug purposes, it should be hidden
        m_treeView.append_column("Id valid", m_columns.m_col_id_valid);
        m_treeView.append_column_editable("Name", m_columns.m_col_name);
        enableEditNextField(
            {m_treeView.get_column(0), m_treeView.get_column(2)});

        add_row(1, true, "Row 1");
        add_row(2, false, "Row 2");
        add_row(3, true, "Row 3");
        add_row(4, false, "Row 4");
    }

    Gtk::TreeView& getTreeView() { return m_treeView; }

private:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() {
            add(m_col_id);
            add(m_col_id_valid);
            add(m_col_name);
        }

        Gtk::TreeModelColumn<int> m_col_id;
        Gtk::TreeModelColumn<bool> m_col_id_valid;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    };
    void add_row(int id, bool id_valid, const std::string& name) {
        auto row = *(m_treeModel->append());
        row[m_columns.m_col_id] = id;
        row[m_columns.m_col_id_valid] = id_valid;
        row[m_columns.m_col_name] = name;
    }
    Gtk::TreeView m_treeView;
    ModelColumns m_columns;
    Glib::RefPtr<Gtk::ListStore> m_treeModel;
};

class MyApp : public Gtk::Application {
public:
    MyApp() : Gtk::Application("org.rasmus.testapp") {
        Glib::set_application_name("edit-row");
    }

    static Glib::RefPtr<MyApp> create() {
        return Glib::RefPtr<MyApp>(new MyApp());
    }
    void on_activate() override { create_window(); }

private:
    void create_window() {
        auto window = new Gtk::ApplicationWindow();
        window->add(m_treeView.getTreeView());
        window->set_default_size(640, 480);
        add_window(*window);
        window->show_all();
    }
    MyTreeView m_treeView;
};

int main(int argc, char** argv) {
    auto app = MyApp::create();
    return app->run(argc, argv);
}
