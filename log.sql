-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Use .schema to have a notion on the tables
.schema
-- Start with all the crime scene reports to see if there's any info
select * from crime_scene_reports;
-- | 295 | 2021 | 7     | 28  | Humphrey Street      | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.|
-- take a look into the interview table
select * from interviews where year='2021' AND month = '7' AND day = '28';
-- check for flight tickets on the first flight the next day, check for phone calls with half an hour duration, check for Leggett Street money withdraw, check bakery parking within 10 minutes from robery
-- star checking the park log
select * from bakery_security_logs where year = '2021' AND month = '7' AND day = '28' AND hour = 10 AND minute >=5 AND minute <= 25 AND activity = 'exit';
--| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
--| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
--| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
--| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
--| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
--| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
--| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
--| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
-- Check flights
select * from flights where year = '2021' and month = '7' and day = '29' ORDER BY hour ASC, minute ASC;
-- first flight | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
-- check if this flight is leaving fiftyville
select * from airports where id = '8';
-- it is, then check the airport 4
select * from airports where id = '4';
-- | 4  | LGA          | LaGuardia Airport | New York City |
-- the thief escaped to New York City
-- check passengers on the flight
select * from passengers where flight_id = '36';
--| 7214083635      | 2A   |
--| 1695452385      | 3B   |
--| 5773159633      | 4A   |
--| 1540955065      | 5C   |
--| 8294398571      | 6C   |
--| 1988161715      | 6D   |
--| 9878712108      | 7A   |
--| 8496433585      | 7B   |
-- The thief might be one of the passengers above
-- check for people in this list that are in the list of the security log
select distinct people.id, people.name, people.passport_number, people.license_plate, people.phone_number FROM people INNER JOIN bakery_security_logs, passengers ON people.passport_number = passengers.passport_number AND people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN (select license_plate from bakery_security_logs where year = '2021' AND month = '7' AND day = '28' AND hour = 10 AND minute >=5 AND minute <= 25 AND activity = 'exit') AND people.passport_number IN (select passport_number from passengers where flight_id = '36');
-- suspects
--|   id   |  name  | passport_number | license_plate |  phone_number  |
--| 398010 | Sofia  | 1695452385      | G412CB7       | (130) 555-0289 |
--| 467400 | Luca   | 8496433585      | 4328GD8       | (389) 555-5198 |
--| 560886 | Kelsey | 8294398571      | 0NTHK55       | (499) 555-9472 |
--| 686048 | Bruce  | 5773159633      | 94KL13X       | (367) 555-5533 |
-- check for the phone calls
select * from phone_calls where year = '2021' AND month = '7' AND day = '28' AND duration <= '60' AND caller IN (select distinct people.phone_number FROM people INNER JOIN bakery_security_logs, passengers ON people.passport_number = passengers.passport_number AND people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN (select license_plate from bakery_security_logs where year = '2021' AND month = '7' AND day = '28' AND hour = 10 AND minute >=5 AND minute <= 25 AND activity = 'exit') AND people.passport_number IN (select passport_number from passengers where flight_id = '36'));
--| 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
--| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
--| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
--| 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
select id, name from people where phone_number = '(130) 555-0289' OR phone_number = '(499) 555-9472' OR phone_number = '(367) 555-5533';
-- suspect list
--| 398010 | Sofia  |
--| 560886 | Kelsey |
--| 686048 | Bruce  |
-- check for bank withdraw
select * from atm_transactions where atm_location like 'Leggett Street' AND day = '28' AND year = '2021' AND month = '7' AND account_number IN (select account_number from bank_accounts where person_id IN (select id from people where phone_number = '(130) 555-0289' OR phone_number = '(499) 555-9472' OR phone_number = '(367) 555-5533'));
-- The thief transaction was
--| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
select * from people where id IN (select person_id from bank_accounts where account_number = '49610011');
-- The thief was Bruce
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- Check the accomplice
select * from phone_calls where year = '2021' AND month = '7' AND day = '28' AND duration <= '60' AND caller = '(367) 555-5533';
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
-- accomplice number is (375) 555-8161
select * from people where phone_number = '(375) 555-8161';
-- | 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |
-- the accomplice was Robin
