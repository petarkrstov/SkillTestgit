#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "avr8-stub.h"
#include "app_api.h" // only needed with flash breakpoints
#include "funkcii.h"

void Task_Print1(void *parameter);
void Task_Print2(void *parameter);
void Task_Led(void *parameter);
void Task_Time(void *parameter);

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;
TaskHandle_t Task_HandleLed;
TaskHandle_t Task_HandleTime;

void setup()
{
  debug_init();
  Serial.begin(9600);
  // Ime na funkcija, Name of task, Stack memmory, parameter, priority, &TaskHandle_t name
  xTaskCreate(Task_Print1, "Task1", 100, NULL, 1, &Task_Handle1);
  xTaskCreate(Task_Print2, "Task2", 100, NULL, 1, &Task_Handle2);
  xTaskCreate(Task_Led, "TaskLed", 100, NULL, 1, &Task_HandleLed);
  xTaskCreate(Task_Time, "TaskTime", 100, NULL, 1, &Task_HandleTime);
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