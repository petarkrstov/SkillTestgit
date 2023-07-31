#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "avr8-stub.h"
#include "app_api.h" // only needed with flash breakpoints
#include "funkcii.h"

void Task_Print1(void *parameter);
void Task_Print2(void *parameter);
void Task_Led(void *parameter);
void Task_Time(void *parameter);

void Task_ReadSerial1(void *parameter);
void Task_ReadSerial2(void *parameter);
void Task_ReadSerial3(void *parameter);

void Task_WriteSerial1(void *parameter);
void Task_WriteSerial2(void *parameter);
void Task_WriteSerial3(void *parameter);

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;
TaskHandle_t Task_HandleLed;
TaskHandle_t Task_HandleTime;

TaskHandle_t Task_HandleReadSerial1;
TaskHandle_t Task_HandleReadSerial2;
TaskHandle_t Task_HandleReadSerial3;

TaskHandle_t Task_HandleWriteSerial1;
TaskHandle_t Task_HandleWriteSerial2;
TaskHandle_t Task_HandleWriteSerial3;

String readSerial1 = "";
String readSerial2 = "";
String readSerial3 = "";
char cSerial1;
char cSerial2;
char cSerial3;

String writeSerial1 = "";
String writeSerial2 = "";
String writeSerial3 = "";
size_t writeSerial1Length = writeSerial1.length();
size_t writeSerial2Length = writeSerial2.length();
size_t writeSerial3Length = writeSerial3.length();

void setup()
{
  // debug_init();
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  // Ime na funkcija, Name of task, Stack memmory, parameter, priority, &TaskHandle_t name
  xTaskCreate(Task_Print1, "Task1", 100, NULL, 1, &Task_Handle1);
  xTaskCreate(Task_Print2, "Task2", 100, NULL, 1, &Task_Handle2);
  xTaskCreate(Task_Led, "TaskLed", 100, NULL, 1, &Task_HandleLed);
  xTaskCreate(Task_Time, "TaskTime", 100, NULL, 1, &Task_HandleTime);

  xTaskCreate(Task_ReadSerial1, "ReadSerial1", 100, NULL, 1, &Task_HandleReadSerial1);
  xTaskCreate(Task_ReadSerial2, "ReadSerial2", 100, NULL, 1, &Task_HandleReadSerial2);
  xTaskCreate(Task_ReadSerial3, "ReadSerial3", 100, NULL, 1, &Task_HandleReadSerial3);

  xTaskCreate(Task_WriteSerial1, "WriteSerial1", 100, NULL, 1, &Task_HandleWriteSerial1);
  xTaskCreate(Task_WriteSerial2, "WriteSerial2", 100, NULL, 1, &Task_HandleWriteSerial2);
  xTaskCreate(Task_WriteSerial3, "WriteSerial3", 100, NULL, 1, &Task_HandleWriteSerial3);

  pinMode(13, OUTPUT);
}

void loop()
{
  // No code here!!!
  // It will print on serial whenever CPU is in idle
  // Serial.println(F("Loop function"));
  // delay(15);
}

void Task_Print1(void *parameter)
{
  (void)parameter;
  // Loop for this task
  while (1)
  {
    Serial.println("Task1");
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void Task_Print2(void *parameter)
{
  (void)parameter;
  // Loop for this task
  while (1)
  {
    Serial.println("Task2");
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void Task_Led(void *parameter)
{
  (void)parameter;
  // Loop for this task
  while (1)
  {
    digitalWrite(13, HIGH);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    digitalWrite(13, LOW);
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void Task_Time(void *parameter)
{
  (void)parameter;
  // Loop for this task
  while (1)
  {
    unsigned long currentTime = millis(); // Get current time in milliseconds

    // Convert milliseconds to seconds, minutes, and hours
    unsigned long seconds = currentTime / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;

    // Calculate remaining seconds and minutes
    seconds = seconds % 60;
    minutes = minutes % 60;

    // Print the elapsed time to the serial console
    Serial.print("Time Elapsed: ");
    Serial.print(hours);
    Serial.print("h ");
    Serial.print(minutes);
    Serial.print("m ");
    Serial.print(seconds);
    Serial.println("s");

    vTaskDelay(5000 / portTICK_PERIOD_MS); // Wait for 1 second before printing again
  }
}

void Task_ReadSerial1(void *parameter)
{
  (void)parameter;
  // Loop for this task
  while (1)
  {
    while (Serial1.available())
    {
      char cSerial1 = (char)Serial1.read();
      readSerial1 += cSerial1;
      if (cSerial1 == '\n')
        readSerial1 = "";
    }
  }
}

void Task_ReadSerial2(void *parameter)
{
  (void)parameter;
  // Loop for this task
  while (1)
  {
    while (Serial2.available())
    {
      char cSerial2 = (char)Serial2.read();
      readSerial2 += cSerial2;
      if (cSerial2 == '\n')
        readSerial2 = "";
    }
  }
}

void Task_ReadSerial3(void *parameter)
{
  (void)parameter;
  // Loop for this task
  while (1)
  {
    while (Serial3.available())
    {
      char cSerial3 = (char)Serial3.read();
      readSerial3 += cSerial3;
      if (cSerial3 == '\n')
        readSerial3 = "";
    }
  }
}

void Task_WriteSerial1(void *parameter)
{
  (void)parameter;
  // Loop for this task
  while (1)
  {
    const uint8_t *writeSerial1Array = (const uint8_t *)writeSerial1.c_str();
    Serial1.write(writeSerial1Array, writeSerial1Length);
  }
}

void Task_WriteSerial2(void *parameter)
{
  (void)parameter;
  // Loop for this task
  while (1)
  {
    const uint8_t *writeSerial2Array = (const uint8_t *)writeSerial2.c_str();
    Serial1.write(writeSerial2Array, writeSerial2Length);
  }
}

void Task_WriteSerial3(void *parameter)
{
  (void)parameter;
  // Loop for this task
  while (1)
  {
    const uint8_t *writeSerial3Array = (const uint8_t *)writeSerial3.c_str();
    Serial1.write(writeSerial3Array, writeSerial3Length);
  }
}