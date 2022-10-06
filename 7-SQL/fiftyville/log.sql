-- Checking reports from same date and place
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street";

-- Checking transcript from inteviews
SELECT transcript FROM interviews WHERE month = 7 AND day = 28 AND transcript LIKE "%bakery%";

-- Filtering account numbers from ATM from the same day
SELECT account_number
FROM atm_transactions
WHERE month = 7
AND day = 28
AND year = 2021
AND atm_location = "Leggett Street";

-- Getting ID number from people on ATM
SELECT * FROM bank_accounts
WHERE account_number IN
    (SELECT account_number
    FROM atm_transactions
    WHERE month = 7
    AND day = 28
    AND year = 2021
    AND atm_location = "Leggett Street");

-- Checking flights leaving town
SELECT * FROM flights
WHERE year = 2021
AND day = 29
AND origin_airport_id =
    (SELECT id
    FROM airports
    WHERE city = "Fiftyville");
-- 5 Flights leaving on the 29th
-- destination_airport_id = [6, 11, 4, 1, 9]



-- Checking flight destination
SELECT DISTINCT airports.city, airports.full_name
    FROM airports
    JOIN flights
    ON flights.destination_airport_id = airports.id
    WHERE airports.id IN
        (SELECT destination_airport_id
        FROM flights
        WHERE year = 2021
        AND day = 29
        AND origin_airport_id =
            (SELECT id
            FROM airports
            WHERE city = "Fiftyville"));
-- Flights heading to Chicago, NYC, Boston, San Francisco and Tokyo


-- Checking info from passengers leaving town
SELECT name
FROM people
WHERE passport_number IN
(SELECT passport_number
    FROM passengers
    WHERE flight_id IN
            (SELECT id
            FROM flights
            WHERE year = 2021
            AND month = 7
            AND day = 29
            AND origin_airport_id =
                (SELECT id
                FROM airports
                WHERE city = "Fiftyville")));


-- Identifying people on ATM
SELECT * FROM people
WHERE id IN
    (SELECT person_id FROM bank_accounts
    WHERE account_number IN
            (SELECT account_number
            FROM atm_transactions
            WHERE month = 7
            AND day = 28
            AND year = 2021
            AND atm_location = "Leggett Street"));
-- People: Kenny, Iman, Benista, Taylor, Brooke, Luca, Diana, Bruce and Kaelyn


-- Checking bakery security logs
SELECT * FROM bakery_security_logs
    WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10;


-- Checking license plates from the same day and hour
SELECT * FROM people
WHERE license_plate IN
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7
    AND day = 28
    AND year = 2021
    AND hour = 10
    AND minute < 30
    AND activity = "exit");

-- Getting names from people that were on the ATM and bakery on 7/28 at 10am
SELECT name
FROM people
WHERE license_plate IN
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7
    AND day = 28
    AND year = 2021
    AND hour = 10
    AND minute < 30
    AND activity = "exit")
INTERSECT
SELECT name
FROM people
WHERE id IN
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE month = 7
        AND day = 28
        AND year = 2021
        AND atm_location = "Leggett Street"
        AND transaction_type = "withdraw"));
-- Suspects: Bruce, Diana, Iman, Luca


-- Crossing info from passengers, ATM and license plate
SELECT name
FROM people
WHERE passport_number IN
(SELECT passport_number
    FROM passengers
    WHERE flight_id IN
            (SELECT id
            FROM flights
            WHERE year = 2021
            AND month = 7
            AND day = 29
            AND origin_airport_id =
                (SELECT id
                FROM airports
                WHERE city = "Fiftyville")))
INTERSECT
SELECT name
FROM people
WHERE license_plate IN
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7
    AND day = 28
    AND year = 2021
    AND hour = 10
    AND minute < 30
    AND activity = "exit")
INTERSECT
SELECT name
FROM people
WHERE id IN
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE month = 7
        AND day = 28
        AND year = 2021
        AND atm_location = "Leggett Street"
        AND transaction_type = "withdraw"));
-- Suspects: Bruce, Diana, Luca


-- Checking phone records
SELECT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;


-- Crossing info again
SELECT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60
INTERSECT
SELECT name
FROM people
WHERE passport_number IN
(SELECT passport_number
    FROM passengers
    WHERE flight_id IN
            (SELECT id
            FROM flights
            WHERE year = 2021
            AND month = 7
            AND day = 29
            AND origin_airport_id =
                (SELECT id
                FROM airports
                WHERE city = "Fiftyville")))
INTERSECT
SELECT name
FROM people
WHERE license_plate IN
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7
    AND day = 28
    AND year = 2021
    AND hour = 10
    AND minute < 30
    AND activity = "exit")
INTERSECT
SELECT name
FROM people
WHERE id IN
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE month = 7
        AND day = 28
        AND year = 2021
        AND atm_location = "Leggett Street"
        AND transaction_type = "withdraw"));
-- Common Suspects: Bruce, Diana


-- Checking flights again, this time looking for the destination of the earliest flight
SELECT DISTINCT city
FROM airports
JOIN flights
ON flights.destination_airport_id = airports.id
WHERE airports.id =
    (SELECT destination_airport_id FROM flights
    WHERE year = 2021
    AND month = 7
    AND day = 29
    AND origin_airport_id =
        (SELECT id
        FROM airports
        WHERE city = "Fiftyville")
    ORDER BY hour, minute
    LIMIT 1);
-- ESCAPED TO NYC!!!


-- Checking which suspect is on the flight
SELECT name
FROM people
JOIN passengers
ON passengers.passport_number = people.passport_number
WHERE flight_id =
        (SELECT id FROM flights
        WHERE year = 2021
        AND month = 7
        AND day = 29
        AND origin_airport_id =
            (SELECT id
            FROM airports
            WHERE city = "Fiftyville")
        ORDER BY hour, minute
        LIMIT 1)
AND name IN
(SELECT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60
INTERSECT
SELECT name
FROM people
WHERE passport_number IN
(SELECT passport_number
    FROM passengers
    WHERE flight_id IN
            (SELECT id
            FROM flights
            WHERE year = 2021
            AND month = 7
            AND day = 29
            AND origin_airport_id =
                (SELECT id
                FROM airports
                WHERE city = "Fiftyville")))
INTERSECT
SELECT name
FROM people
WHERE license_plate IN
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7
    AND day = 28
    AND year = 2021
    AND hour = 10
    AND minute < 30
    AND activity = "exit")
INTERSECT
SELECT name
FROM people
WHERE id IN
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE month = 7
        AND day = 28
        AND year = 2021
        AND atm_location = "Leggett Street"
        AND transaction_type = "withdraw")));
-- BRUCE DID IT!!!


-- Checking who did Bruce call
SELECT name
FROM people
WHERE phone_number IN
    (SELECT receiver
    FROM phone_calls
    WHERE year = 2021
    AND month = 07
    AND day = 28
    AND duration < 60
    AND caller =
        (SELECT phone_number
        FROM people
        WHERE name = "Bruce"));
-- ROBIN HELPED!!!!