SELECT people.name
FROM people
JOIN directors, ratings
ON directors.movie_id = ratings.movie_id
AND directors.person_id = people.id
WHERE ratings.rating >= 9.0;