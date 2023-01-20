select distinct name from people
join stars on stars.person_id = people.id
join movies on stars.movie_id = movies.id
where movies.id
IN
(SELECT movie_id FROM stars JOIN people ON people.id = stars.person_id WHERE people.name = "Kevin Bacon" AND people.birth = 1958)
AND
people.name != "Kevin Bacon"