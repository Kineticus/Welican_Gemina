<template>
<div>
  <section class="hero is-info container">
    <div class="hero-body">
      <h2 class="title">USERS</h2>
      <b-table 
      :bordered="false"
      :striped="true"
      :narrowed="true"
      :hoverable="true"
      :loading="isLoading"
      :focusable="false"
      :mobile-cards="false"
      :data="users" :columns="columns"></b-table>
    </div>
  </section>
<!-- <table class="table is-bordered is-striped is-narrow is-hoverable is-fullwidth">
    <thead>
      <tr>
        <th><abbr title="Id">Id</abbr></th>
        <th><abbr title="name">Name</abbr></th>
        <th><abbr title="wifiName">WiFi Name</abbr></th>
        <th><abbr title="createdDate">Created Date</abbr></th>
        <th><abbr title="zipcode">Zipcode</abbr></th>
        <th><abbr title="timezone">Timezone</abbr></th>
      </tr>
    </thead>
    <tbody>
        <tr v-for="user in users" :key="user.id" class="modal-button" data-target="user-modal" v-on:click="userClicked(user)">
          <td>{{user.id}}</td>
          <td>{{user.name}}</td>
          <td>{{user.wifiName}}</td>
          <td>{{user.createdDate}}</td>
          <td>{{user.zipcode}}</td>
          <td>{{user.timezone}}</td>
        </tr>
    </tbody>
  </table> -->

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