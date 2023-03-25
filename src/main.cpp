#include <Arduino.h>
#include <ThingifyEsp.h>

ThingifyEsp thing("Esp32SampleThing");
Node* switchNode;
bool previousSwitchState = false;
const int RelayPin = 4;
const int SwitchPin = 5;

bool OnBoolChanged(void*_, Node *node)
{
    digitalWrite(RelayPin, node->Value.AsBool());
    return true;
}

void setup()
{
    thing.Initialize();
    Serial.begin(500000);	
    thing.AddDiagnostics();

    pinMode(SwitchPin, INPUT);
    pinMode(RelayPin, OUTPUT);

    switchNode = thing.AddBoolean("Switch")->OnChanged(OnBoolChanged);
    thing.Start();
}

void loop()
{
    auto switchState = digitalRead(SwitchPin);
    if(switchState != previousSwitchState)
    {
        switchNode->SetValue(NodeValue::Boolean(!switchNode->Value.AsBool()));
    }
    previousSwitchState = switchState;

    thing.Loop();
}
