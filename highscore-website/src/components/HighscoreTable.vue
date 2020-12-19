<template>
  <div>
    <section class="hero is-light">
      <div class="hero-body">
        <h2 class="title">{{this.game}} HIGHSCORES</h2>
        <b-table 
        :data="highscores" 
        :paginated="true"
        :per-page="5"
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
        aria-current-label="Current page">
          <b-table-column field="id" label="ID" width="40" v-slot="props">
              {{ props.row.id }}
          </b-table-column>

          <b-table-column field="highscore" label="Score" sortable numeric v-slot="props">
              {{ props.row.highscore }}
          </b-table-column>
        </b-table>
      </div>
    </section>
  </div>
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
      paginationPosition: 'bottom',
      defaultSortDirection: 'desc',
      sortIcon: 'arrow-up',
      sortIconSize: 'is-small',
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