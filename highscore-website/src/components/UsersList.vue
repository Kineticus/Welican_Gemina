<template>
<div>
  <section class="hero is-info container">
    <div class="hero-body">
      <h2 class="title">USERS</h2>
      <b-table 
      :data="users" 
      :paginated="true"
      :per-page="10"
      :bordered="false"
      :striped="true"
      :narrowed="true"
      :hoverable="true"
      :loading="isLoading"
      :focusable="false"
      :mobile-cards="false"
      :pagination-simple="false"
      :pagination-position="paginationPosition"
      :default-sort-direction="defaultSortDirection"
      :sort-icon="sortIcon"
      :sort-icon-size="sortIconSize"
      default-sort="highscore"
      aria-next-label="Next page"
      aria-previous-label="Previous page"
      aria-page-label="Page"
      aria-current-label="Current page"
      >
        <b-table-column field="id" label="ID" width="40" v-slot="props">
            {{ props.row.id }}
        </b-table-column>
        <b-table-column field="name" label="Name" sortable numeric v-slot="props">
            {{ props.row.name }}
        </b-table-column>
        <b-table-column field="wifiName" label="Wifi Name" sortable numeric v-slot="props">
            {{ props.row.wifiName }}
        </b-table-column>
        <b-table-column field="createdDate" label="Created Date" sortable numeric v-slot="props">
            {{ props.row.createdDate }}
        </b-table-column>
        <b-table-column field="zipcode" label="Zipcode" sortable numeric v-slot="props">
            {{ props.row.zipcode }}
        </b-table-column>
        <b-table-column field="timezone" label="timezone" sortable numeric v-slot="props">
            {{ props.row.timezone }}
        </b-table-column>
      </b-table>
    </div>
  </section>

<div id="user-modal" class="modal">
  <div class="modal-background"></div>
  <div class="modal-card">
    <header class="modal-card-head">
      <p class="modal-card-title">{{this.selectedUser.id}}</p>
      <button class="delete" aria-label="close"></button>
    </header>
    <section class="modal-card-body">
      <h1>{{this.selectedUser.name}}</h1>
      <h2>{{this.selectedUser.wifiName}}</h2>
      <h3>{{this.selectedUser.createdDate}}</h3>
      <h4>{{this.selectedUser.zipcode}}</h4>
      <h4>{{this.selectedUser.timezone}}</h4>

      <div v-for="(value, game, index) in this.selectedUser.games" :key="index">
            <div v-if="game == 'fallios'">
Fallios: {{value.highscore}}
            </div>
            <div v-if="game == 'block-breaker'">
Block Breaker: {{value.highscore}}
            </div>
            <div v-if="game == 'daddy-worm'">
1p: {{value.highscore}}
2p: {{value.highscore2p}}
            </div>
      </div>
    </section>
    <footer class="modal-card-foot">
      <!-- <button class="button is-success">Save changes</button> -->
      <button class="button">Cancel</button>
    </footer>
  </div>
</div>
</div>
</template>

<script>
import moment from 'moment';
import UsersDataService from "../services/usersDataService";
export default {
  name: "users-list",
  components: {
  },
  data() {
    return {
      isLoading: false,
      paginationPosition: 'bottom',
      defaultSortDirection: 'desc',
      sortIcon: 'arrow-up',
      sortIconSize: 'is-small',
      selectedUser: {},
      users: [],
      columns: [
          {
            field: 'id',
            label: 'ID',
            width: '40',
          },
          {
            field: 'name',
            label: 'Name',
            numeric: false
          },
          {
            field: 'wifiName',
            label: 'Wifi Name',
            numeric: false
          },
          {
            field: 'createdDate',
            label: 'Created Date',
            numeric: false
          },
          {
            field: 'zipcode',
            label: 'Zipcode',
            numeric: false
          },
          {
            field: 'timezone',
            label: 'Timezone',
            numeric: false
          }
      ]
    };
  },
  methods: {
    userClicked(user) {
      console.log("SELECTED USER", user);
      this.selectedUser = user;
      this.selectedUser.games = user.games;
    },
    onDataChange(items) {
      let _users = [];
      items.forEach((item) => {
        var user = item.val();
        _users.push({
          id: item.key,
          name: user.name,
          games: user.games,
          wifiName: user.wifiName,
          createdDate: moment(user.createdDate).format("DD/MM/YYYY hh:mm:ss a"),
          timezone: user.timezone,
          zipcode: user.zipcode,
        });
      });
      this.isLoading = false;
      this.users = _users;
    },
  },
  mounted() {
    this.isLoading = true;
    UsersDataService.getAll().then((snapshot) => {
        console.log("/Users", snapshot.val());
        this.onDataChange(snapshot);
    });
  },
  beforeUnmount() {
  }
};
</script>

<style>

</style>