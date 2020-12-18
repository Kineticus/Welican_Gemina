<template>
<div>
  <section class="hero is-light">
    <div class="hero-body">
      <h2 class="title">{{this.game}} HIGHSCORES</h2>
      <b-table 
      :bordered="false"
      :striped="true"
      :narrowed="true"
      :hoverable="true"
      :loading="isLoading"
      :focusable="false"
      :mobile-cards="false"
      :data="highscores" :columns="columns"></b-table>
    </div>
  </section>
</div>
   <!-- <div>
      <h2>{{this.game}} HIGHSCORES</h2>
<table class="table is-bordered is-striped is-narrow is-hoverable is-fullwidth">
    <thead>
      <tr>
        <th><abbr title="Id">Id</abbr></th>
        <th><abbr title="name">Highscore</abbr></th>
      </tr>
    </thead>
    <tbody>
        <tr v-for="hs in highscores" :key="hs.id">
          <td>{{hs.id}}</td>
          <td>{{hs.highscore}}</td>
        </tr>
    </tbody>
  </table>
   </div> -->
</template>

<script>
import UsersDataService from "../services/usersDataService";

export default {
  name: "highscore-table",
  components: {
  },
  data() {
    return {
      game: this.$attrs.game,
      highscores: [],
      isLoading: false,
      data: [
          { 'id': 1, 'first_name': 'Jesse', 'last_name': 'Simmons', 'date': '2016-10-15 13:43:27', 'gender': 'Male' },
          { 'id': 2, 'first_name': 'John', 'last_name': 'Jacobs', 'date': '2016-12-15 06:00:53', 'gender': 'Male' },
          { 'id': 3, 'first_name': 'Tina', 'last_name': 'Gilbert', 'date': '2016-04-26 06:26:28', 'gender': 'Female' },
          { 'id': 4, 'first_name': 'Clarence', 'last_name': 'Flores', 'date': '2016-04-10 10:28:46', 'gender': 'Male' },
          { 'id': 5, 'first_name': 'Anne', 'last_name': 'Lee', 'date': '2016-12-06 14:38:38', 'gender': 'Female' }
      ],
      columns: [
          {
            field: 'id',
            label: 'MAC Address',
            width: '40',
          },
          {
            field: 'highscore',
            label: 'Score',
            numeric: true
          }
      ]
    };
  },
  methods: {
    onDataChange(items) {
      let _highScores = [];
      items.forEach((item) => {
        var hs = item.val();
        _highScores.push({
          id: item.key,
          highscore: hs,
        });
      });
      this.isLoading = false;
      this.highscores = _highScores;
    }
  },
  mounted() {
    this.isLoading = true;
    UsersDataService.getSpecificHighscores(this.game).then((snapshot) => {
        console.log("/Highscores", snapshot.val());
        this.onDataChange(snapshot);
    });
  },
  beforeUnmount() { 
  }
}
</script>

<style>
  h2.title {
    text-transform: uppercase;
  }
</style>