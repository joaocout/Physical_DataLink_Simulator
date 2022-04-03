#include <gtkmm.h>

class MyWindow : public Gtk::Window
{

    Gtk::Fixed m_fixed;
    Gtk::Box m_box1, m_box2;
    Gtk::Alignment m_alignment1;
    Gtk::Entry m_entry1;
    Gtk::Label m_label1;
    Gtk::Button m_button1;
    Gtk::Frame m_frame1;
    Gtk::LinkButton m_linkbutton;
    


public:
    MyWindow();
    void set_hierarchy();
    void draw_widgets();
};

MyWindow::MyWindow() : m_box1{Gtk::Orientation::ORIENTATION_VERTICAL}, m_box2{Gtk::Orientation::ORIENTATION_VERTICAL}
{
    set_hierarchy();
    draw_widgets();
}

void MyWindow::set_hierarchy(){
  // Window
  add( m_fixed );

  // Fixed
  m_fixed.add( m_frame1 );

  // Frame 1
  m_frame1.add( m_box1 );
  m_frame1.set_label("UMA MAQUINA");

  // Box 1
  m_box1.add( m_alignment1 );
  m_box1.add( m_label1 );
  m_box1.add( m_button1 );

  // Alignment 1
  m_alignment1.add( m_box2 );

  // Box 2
  m_box2.pack_start( m_entry1, true, true, 0 );

}

void MyWindow::draw_widgets(){
  // Window
  set_title("Simulador");
  set_default_size( 300, 400 );
  set_visible( true );
  set_can_focus( false );
  set_resizable( false );
  set_border_width( 6 );

  // Fixed
  m_fixed.set_size_request( 300, 400 );
  m_fixed.set_visible( true );
  m_fixed.set_can_focus( false );

  // Frame 1
  m_frame1.set_size_request( 100, 80 );
  m_frame1.set_visible( true );
  m_frame1.set_can_focus( false );
  m_frame1.set_margin_end( 8 );
  m_frame1.set_shadow_type( Gtk::ShadowType::SHADOW_IN );
  m_frame1.set_label_align( 0.02 );

  // Box 1
  m_box1.set_visible( true );
  m_box1.set_can_focus( false );

  // Alignment 1
  m_alignment1.set_size_request( 400, 62 );
  m_alignment1.set_visible( true );
  m_alignment1.set_can_focus( true );
  m_alignment1.set_border_width( 10 );

  // Box 2
  m_box2.set_visible( true );
  m_box2.set_can_focus( false );
  

  // Entry 1
  m_entry1.set_visible( true );
  m_entry1.set_visibility( false );
  m_entry1.set_can_focus( true );
  m_entry1.set_placeholder_text("Insira sua mensagem");
  m_entry1.set_input_purpose( Gtk::INPUT_PURPOSE_PASSWORD );
  m_entry1.set_max_length( 32 );

  // Button 1
  m_button1.set_label("XAMA");
  m_button1.set_visible( true );
  m_button1.set_can_focus( true );
  m_button1.set_focus_on_click( true );
  m_button1.set_border_width( 5 );
}

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    MyWindow window;
    return app->run(window);
}