const filterDD = document.getElementById('project-dropdown')
const filterButton = document.getElementById('filter-button')
const clearFilterButton = document.getElementById('clear-filter-button')
const table = document.getElementById('emp-table')

filterButton.addEventListener('click', function(e) {
    window.location = `/filter/${filterDD.value}`
})

clearFilterButton.addEventListener('click', function(e) {
    window.location = '/'
})