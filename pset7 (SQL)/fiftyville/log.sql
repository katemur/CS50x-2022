-- Keep a log of any SQL queries you execute as you solve the mystery
--getting the description of the crome scene
SELECT description FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28
AND street = "Chamberlin Street";
-- OUTPUT: time - 10:15am; place:Chamberlin Street courthouse. Interviews with three witnesses who were present at the time each of their interview
-- transcripts mentions the courthouse.
-- looking for interviews
SELECT transcript FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%courthouse%";
-- Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- they called someone who talked to them for less than a minute.
--the thief s were planning to take the earliest flight out of Fiftyville tomorrow.
--The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- figuring out who was at the ATM on fifer street
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE bank_accounts.account_number IN
(SELECT account_number FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street");
-- OUTPUT Ernest; Robert; Russell; Roy; Bobby; Elizabeth; Danielle; Madison; Victoria
-- getting who of them was in the courthouse this morning
SELECT DISTINCT (name) FROM people
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
WHERE courthouse_security_logs.license_plate IN
(SELECT license_plate FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10);
-- OUTPUT: Thomas; Jeremy; Sophia; Elizabeth; Ernest; Madison; Russell; Evelyn; Danielle; Patrick; Amber; Roger; Brandon; Denise
-- SUSPECTS: Ernest; Russel; Elizabeth; Danielle; Madison; 
-- finding out who made calls that day that lasted less than a minute
SELECT DISTINCT (name) FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE phone_calls.caller IN
(SELECT caller FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60);
-- OUTPUT: Ernest; Madison; Evelyn; Roger; Russell; Kimberly; Victoria; Bobby
-- SUSPECTS: Ernest; Russel; Madison; 
-- finding out the name of the fiftyville airport
SELECT full_name FROM airports
WHERE city = "Fiftyville";
-- OUTPUT: Fiftyville Regional Airport;
-- getting list of flights from fiftyville on the next day
SELECT hour, minute FROM flights
JOIN airports ON airports.id = flights.origin_airport_id
WHERE airports.full_name = "Fiftyville Regional Airport" AND year = 2020 AND month = 7 AND day = 29;
-- the earliest flight is at 8:20
-- getting the destination city
SELECT city FROM airports
JOIN flights ON destination_airport_id = airports.id
WHERE destination_airport_id IN
(SELECT destination_airport_id FROM flights
JOIN airports ON airports.id = flights.origin_airport_id
WHERE airports.full_name = "Fiftyville Regional Airport" AND year = 2020 AND month = 7 AND day = 29 AND hour = 8 AND minute = 20);
-- Escape city is London
SELECT DISTINCT(name) FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.passport_number IN
(SELECT passport_number FROM passengers
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.id IN
(SELECT flights.id FROM flights
JOIN airports ON airports.id = flights.origin_airport_id
WHERE airports.full_name = "Fiftyville Regional Airport" AND year = 2020 AND month = 7 AND day = 29 AND hour = 8 AND minute = 20));
--OUTPUT: Danielle; Doris; Roger; Ernest; Edward; Evelyn; Madison; Bobby
-- A thief is Ernest or Madison
SELECT receiver FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller in (SELECT caller FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE name = "Ernest");
-- Ernest called (375) 555-8161
SELECT receiver FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller in (SELECT caller FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE name = "Madison");
-- Madison called (676) 555-6554
SELECT name FROM people
WHERE phone_number = "(375) 555-8161";
-- Ernest called Berthold
SELECT name FROM people
WHERE phone_number = "(676) 555-6554";
-- Madison called James