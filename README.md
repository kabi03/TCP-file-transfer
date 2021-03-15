##### Full Stack developer - Coding challenge

The following Coding challenge project must be completed and sent over prior to an onsite/remote technical interview at FIIX.

###### General Instructions

1. There is a 1-week deadline to submit a solution, however we ask you not to spend more than a couple of hours to provide a clean and working solution.
2. You may leave things open for discussion during the onsite/remote technical interview.
3. Feel free to get in touch with Hazel Chan if you have any questions.

###### Project Description

The goal of the challenge is to build a Plant Care system that focuses on a watering schedule.
Given a data set containing the names of plants at a nursery, their watering frequency and when they were watered last,
present a time table displaying plants that have been watered, that will need watering soon and those that have watering overdue.

###### Angular SPA
1. Build a basic SPA, either within the provided maven base project or in a different project with a basic tabular component.
2. The time table must display plant names, watering frequency, last watered date and status.
3. Status cells may be text-free but must display one of four colours Green, light green, yellow and red.
4. Status - Green denotes that the plant has been watered as per their frequency requirement.
5. Status - Light green denotes that the plant is due to be watered today or in 1 day.
6. Status - Yellow denotes that watering the plant is overdue by 1 or 2 days.
7. Status - Red denotes that watering the plant is overdue for more than 2 days.
8. Provide a means to upload the current water status data set to the backend.
9. Provide a means to enter watering status for a plant.

###### Spring Boot backend
1. Provide an API to consume the current water status data set.
2. The data set Json to be used is resources/PlantsWateringSchedule.json. 
3. Feel free to add to the data set to allow values to be displayed with pagination.
4. Use the H2 database to persist the data set. Feel free to change to a more familiar DB if required.
5. Provide an API that the SPA will consume in order to populate the Watering Time Table and update individual watering status of the plants.

###### Project Instructions
1. Ensure to follow clean code and SOLID principles.
2. Follow TDD or ensure to have good test coverage.
3. Ensure you follow good coding styles and conventions.

###### Submission Instructions
1. Clone the repository
2. Complete your project as instructed and ensure to commit all the code to your local repo.
3. Create a git bundle and email it to Hazel Chan/Dean Delpeache.

Please Note: Do not create branches and commit code to the remote repository. The repository will be cleaned up periodically and you will end up losing all your code should you push your brances and changes to it.



