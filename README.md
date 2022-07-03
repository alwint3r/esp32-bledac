# BLE-controlled Digital-to-Analog

This code will convert 8 bit (0 - 255) digital value to an analog signal and send it via GPIO 25.
The digital value is configurable through bluetooth low energy.

## Write Value

Use characteristic `83336cef-8fbc-4b77-857b-0aebec87160d` to write the digital value as text.

## Read Value

Use characteristic `83336cef-8fbc-4b77-857b-0aebec87160d` to read the configured digital value.

## Read Voltage

Use characteristic `83336cef-8fbc-4b77-857b-0aebec87160e` to read the configured digital value as millivolt value.
