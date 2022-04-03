#include <gtkmm.h>
#include <iostream>
#include "CamadaFisica.hpp"

class Simulador : public Gtk::Window
{

  Gtk::Fixed fixed;
  Gtk::Box box, box_input;
  Gtk::Alignment alignment;
  Gtk::Entry entry;
  Gtk::Label label;
  Gtk::Button button;
  Gtk::Frame frame;

  public:
    Simulador();
    void set_hierarchy();
    void draw_widgets();
  
  protected:
    void on_button_click();

};

Simulador::Simulador() : box{Gtk::Orientation::ORIENTATION_VERTICAL}, box_input{Gtk::Orientation::ORIENTATION_VERTICAL}
{
    set_hierarchy();
    draw_widgets();
}

void Simulador::on_button_click() {
  string input = entry.get_text();
  std::cout << input << std::endl;

  AplicacaoTransmissora(input);

}

void Simulador::set_hierarchy(){
  add( fixed );

  fixed.add( frame );

  frame.add( box );
  frame.set_label("Transmissor");

  box.add( alignment );
  box.add( label );
  box.add( button );

  alignment.add( box_input );

  box_input.pack_start( entry, true, true, 0 );
}

void Simulador::draw_widgets(){
  set_title("Simulador");
  set_default_size( 300, 400 );
  set_visible( true );
  set_can_focus( false );
  set_resizable( false );
  set_border_width( 6 );

  fixed.set_size_request( 300, 400 );
  fixed.set_visible( true );
  fixed.set_can_focus( false );

  frame.set_size_request( 100, 80 );
  frame.set_visible( true );
  frame.set_can_focus( false );
  frame.set_margin_end( 8 );
  frame.set_label_align( 0.02 );

  box.set_visible( true );
  box.set_can_focus( false );

  alignment.set_size_request( 400, 62 );
  alignment.set_visible( true );
  alignment.set_can_focus( true );
  alignment.set_border_width( 10 );

  box_input.set_visible( true );
  box_input.set_can_focus( false );

  entry.set_visible( true );
  entry.set_can_focus( true );
  entry.set_placeholder_text("Insira sua mensagem");

  button.set_label("Enviar Mensagem");
  button.set_visible( true );
  button.set_can_focus( true );
  button.set_focus_on_click( true );
  button.set_border_width( 5 );
  button.signal_clicked().connect(sigc::mem_fun(*this, &Simulador::on_button_click));
}

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "tr1.simulador");
    Simulador simulador;
    return app->run(simulador);
}