SELECT movies.title
FROM movies
JOIN stars, ratings, people
ON stars.movie_id = ratings.movie_id
AND ratings.movie_id = movies.id
AND stars.person_id = people.id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
limit 5;