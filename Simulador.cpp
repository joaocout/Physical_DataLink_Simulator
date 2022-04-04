#include <gtkmm.h>
#include <iostream>
#include "CamadaFisica.hpp"

class Simulador : public Gtk::Window
{

  Gtk::Fixed fixed;
  Gtk::Box box, box_input, box_radio;
  Gtk::Alignment alignment, alignment_radio;
  Gtk::Entry entry;
  Gtk::Label label;
  Gtk::Button button;
  Gtk::Frame frame_input, frame_radio;
  Gtk::RadioButton::Group button_group;
  Gtk::RadioButton button_binario, button_manchester, button_bipolar;

  public:
    Simulador();
    void set_hierarchy();
    void draw_widgets();
  
  protected:
    void on_button_click();
    void on_button_click_binario();
    void on_button_click_manchester();
    void on_button_click_bipolar();

};

Simulador::Simulador() : box{Gtk::Orientation::ORIENTATION_VERTICAL}, box_input{Gtk::Orientation::ORIENTATION_VERTICAL}, box_radio{Gtk::Orientation::ORIENTATION_VERTICAL}, button_binario("Codificação Binária"), button_manchester("Codificação Manchester"), button_bipolar("Codificação Bipolar")
{
    set_hierarchy();
    draw_widgets();
}

int selected_encoding = 0;

void Simulador::on_button_click_binario() {
  selected_encoding = 0;
}

void Simulador::on_button_click_manchester() {
  selected_encoding = 1;
}

void Simulador::on_button_click_bipolar() {
  selected_encoding = 2;
}

void Simulador::on_button_click() {
  string input = entry.get_text();
  std::cout << input << std::endl;

  //tipo de codificacao desejada
  AplicacaoTransmissora(input, selected_encoding);

}

void Simulador::set_hierarchy(){
  add( fixed );

  fixed.add( frame_input );

  frame_input.add( box );
  frame_input.set_label("Transmissor");

  box.add( alignment );
  box.add( label );
  box.add( button );

  alignment.add( box_input );

  box_input.pack_start( entry, true, true, 0 );

  fixed.add(frame_radio);
  frame_radio.add(box_radio);
  frame_radio.set_label("Tipo de codificação");
  fixed.move(frame_radio, 0, 140);

  box_radio.add(alignment_radio);
  box_radio.add(button_binario);
  box_radio.add(button_manchester);
  box_radio.add(button_bipolar);

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

  frame_input.set_size_request( 100, 0 );
  frame_input.set_visible( true );
  frame_input.set_can_focus( false );
  frame_input.set_margin_end( 8 );
  frame_input.set_label_align( 0.02 );

  box.set_visible( true );
  box.set_can_focus( false );

  alignment.set_size_request( 400, 0 );
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
  
  frame_radio.set_size_request( 100, 50 );
  frame_radio.set_visible( true );
  frame_radio.set_can_focus( false );
  frame_radio.set_margin_end( 8 );
  frame_radio.set_label_align( 0.02 );

  box_radio.set_visible( true );
  box_radio.set_can_focus( false );
  box_radio.set_spacing( 10 );

  alignment_radio.set_size_request( 400, 0 );
  alignment_radio.set_visible(true);
  alignment_radio.set_can_focus(true);
  alignment_radio.set_border_width(10);

  button_binario.set_visible(true);
  button_bipolar.set_visible(true);
  button_manchester.set_visible(true);

  button_binario.set_group(button_group);
  button_bipolar.set_group(button_group);
  button_manchester.set_group(button_group);

  button_binario.signal_clicked().connect(sigc::mem_fun(*this, &Simulador::on_button_click_binario));
  button_manchester.signal_clicked().connect(sigc::mem_fun(*this, &Simulador::on_button_click_manchester));
  button_bipolar.signal_clicked().connect(sigc::mem_fun(*this, &Simulador::on_button_click_bipolar));

}

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "tr1.simulador");
    Simulador simulador;
    return app->run(simulador);
}