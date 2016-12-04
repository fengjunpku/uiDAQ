timer()
{
  TTimer *r = new TTimer(2000);
  r->SetCommand("print()");
  r->TurnOn();
}

void print()
{
  cout<<"ed"<<endl;
}