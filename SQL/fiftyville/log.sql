-- I first read the crime scene reports from the date and location of the robbery.
SELECT * FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";
-- I discovered that each of the interview transcripts for this crime mentions the courthouse.

-- I then selected all the transcripts from the day of the robbery that mention the courthouse.
SELECT transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%courthouse%";
-- From these transcripts, I learned that the theif's car was caught leaving by courthouse security cameras within ten
-- minutes of the crime; that the theif made a withdrawl from the ATM on Fifer Street; and that the theif called his/her
-- accomplice to purchase him/her a ticket on the earliest flight out of Fiftyville for the day after the crime was
-- committed.

-- Next, I checked the courthouse_security_logs for cars that fit the above criteria.
SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 5
    AND minute <= 25 AND activity = "exit";
-- This query returned 8 entries.

-- Then I checked the transactions done at the ATM on Fifer Street
SELECT * FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28
    AND atm_location = "Fifer Street" AND transaction_type = "withdraw";
-- This query also returned 8 entries.

-- I then reviewed the phone calls made on the day of the crime with a duration of less than 60 seconds.
SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;

-- I then identified the earliest flight leaving Fiftyville on the day after the robbery.
SELECT * FROM flights WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1;

-- I combined all the information from above into a single query to identify the theif.
SELECT * FROM people
    WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60)
    AND license_plate IN (SELECT license_plate FROM courthouse_security_logs
        WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 5
        AND minute <= 25 AND activity = "exit")
    AND passport_number IN (SELECT passport_number FROM passengers
        WHERE flight_id = (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29
        ORDER BY hour, minute LIMIT 1))
    AND id IN (SELECT person_id FROM bank_accounts
        WHERE account_number IN (SELECT account_number FROM atm_transactions
            WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street"
            AND transaction_type = "withdraw"));
-- This query returned the entry in people with the name "Ernest"

-- I then selected the destination of the flight that the their (Ernest) took.
SELECT city FROM airports WHERE
    id = (SELECT destination_airport_id FROM flights WHERE
        id IN (SELECT flight_id FROM passengers WHERE
            passport_number = (SELECT passport_number FROM people WHERE name = "Ernest")));

-- Lastly, I found the accomplice based on the phone call that the theif made.
SELECT name FROM people WHERE
    phone_number = (SELECT receiver FROM phone_calls WHERE
        caller = (SELECT phone_number FROM people WHERE
            name = "Ernest"));
